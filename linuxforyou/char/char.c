/* Our First Driver code 
*http://derekmolloy.ie/writing-a-linux-kernel-module-part-2-a-character-device/
* lsmod — lists currently loaded modules
* insmod <module_file> — inserts/loads the specified module file
* modprobe <module> — inserts/loads the module, along with any dependencies
* rmmod <module> — removes/unloads the module
*
*/

#include <linux/init.h>           // Macros used to mark up functions e.g. __init __exit
#include <linux/module.h>         // Core header for loading LKMs into the kernel
#include <linux/version.h>
#include <linux/kernel.h>         // Contains types, macros, functions for the kernel
#include <linux/fs.h>             // Header for the Linux file system support
#include <linux/device.h>         // Header to support the kernel Driver Model
#include <asm/uaccess.h>          // Required for the copy to user function
#include <linux/types.h> 	/* for major and minor number */
//#define  DEVICE_NAME "mynull"    ///< The device will appear at /dev/mynull using this value
//#define  CLASS_NAME  "chardev"        ///< The device class -- this is a character device driver at /sys/class/chardev
#include <linux/cdev.h>
#include <linux/err.h>
static dev_t first; 		// Global variable for the first device number
static struct cdev c_dev; 	// Global variable for the character device structure
static struct class *dcl = NULL; 	// Global variable for the device class
static struct device *ddr = NULL; ///< The device-driver device struct pointer

//static int    majorNumber;                  ///< Stores the device number -- determined automatically
static char   message[256] = {0};           ///< Memory for the string that is passed from userspace
static short  size_of_message;              ///< Used to remember the size of the string stored
static int    numberOpens = 0;              ///< Counts the number of times the device is opened

/** @brief The device open function that is called each time the device is opened
 *  This will only increment the numberOpens counter in this case.
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 */
static int dev_open(struct inode *i, struct file *f)
{
	numberOpens++;
	printk(KERN_INFO "Char: Device has been opened %d time(s)\n", numberOpens);
	return 0;
}
/** @brief The device release function that is called whenever the device is closed/released by
 *  the userspace program
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 */
static int dev_release(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Driver: close()\n");
	return 0;
}
/** @brief This function is called whenever device is being read from user space i.e. data is
 *  being sent from the device to the user. In this case is uses the copy_to_user() function to
 *  send the buffer string to the user and captures any errors.
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 *  @param buffer The pointer to the buffer to which this function writes the data
 *  @param len The length of the b
 *  @param offset The offset if required
 */
static ssize_t dev_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	int error_count = 0;
	// copy_to_user has the format ( * to, *from, size) and returns 0 on success
	error_count = copy_to_user(buf, message, size_of_message);
	if (error_count==0) {            // if true then have success
		printk(KERN_INFO "Char: Sent %d characters to the user\n", size_of_message);
		return (size_of_message=0);  // clear the position to the start and return 0
	}
	else {
		printk(KERN_INFO "Char: Failed to send %d characters to the user\n", error_count);
		return -EFAULT;              // Failed -- return a bad address message (i.e. -14)
	}
	//printk(KERN_INFO "Driver: read()\n");
	return 0;
}
/** @brief This function is called whenever the device is being written to from user space i.e.
 *  data is sent to the device from the user. The data is copied to the message[] array in this
 *  LKM using the sprintf() function along with the length of the string.
 *  @param filep A pointer to a file object
 *  @param buffer The buffer to that contains the string to write to the device
 *  @param len The length of the array of data that is being passed in the const char buffer
 *  @param offset The offset if required
 */
static ssize_t dev_write(struct file *f, const char __user *buf,size_t len, loff_t *off)
{
	sprintf(message, "%s(%d letters)", buf, len);   // appending received string with its length
	size_of_message = strlen(message);                 // store the length of the stored message
	printk(KERN_INFO "EBBChar: Received %d characters from the user\n", len);
	return 0;
}
static struct file_operations char_fops = {
  .owner = THIS_MODULE,
  .open = dev_open,
  .release = dev_release,
  .read = dev_read,
  .write = dev_write
};

/** @brief The LKM initialization function
 *  The static keyword restricts the visibility of the function to within this C file. The __init
 *  macro means that for a built-in driver (not a LKM) the function is only used at initialization
 *  time and that it can be discarded and its memory freed up after that point.
 *  @return returns 0 if successful
 */
static int __init char_init(void) /* Constructor */
{
	//int ret;
	printk(KERN_INFO "Namaskar: module registered\n");
	
//	register_chrdev_region(dev_t, unsigned, const char *);
	if (alloc_chrdev_region(&first, 0, 3, "Dharm") < 0) {
		return -1;
	}
	printk(KERN_INFO "<Major, Minor>: <%d, %d>\n", MAJOR(first), MINOR(first));
	
	/*to create class "chardev" under /sys/class */
	dcl = class_create(THIS_MODULE, "chardev");
	//if ( (dcl = class_create(THIS_MODULE, "chardev")) == NULL ) {
	if(IS_ERR(dcl)) {	// Clean up if there is an error
		printk(KERN_INFO " class chardev is not created successfully\n");
		unregister_chrdev_region(first, 3);	// Repeated code but the alternative is goto statements
		return PTR_ERR(dcl);
	}
	printk(KERN_INFO "Char: device class created successfully\n"); 

	//register the device driver
	/*to create character "mynull" node under /dev */
	//if (device_create(dcl, NULL, first, NULL, "mynull") == NULL)
	ddr = device_create(dcl, NULL, first, NULL, "mynull");
	if(IS_ERR(ddr)) {
		printk(KERN_INFO " device  is not created successfully\n");
		class_destroy(dcl);
		unregister_chrdev_region(first, 3);
		//The PTR_ERR() is a function that is defined in linux/err.h that retrieves the error number from the pointer
		return PTR_ERR(ddr);
	}
	printk(KERN_INFO "Char: device created successfully\n"); 

	cdev_init(&c_dev, &char_fops);
	if (cdev_add(&c_dev, first, 3) == -1)
	{
		printk(KERN_INFO " device  is not added successfully\n");
		class_destroy(dcl);
		device_destroy(dcl,first);
		unregister_chrdev_region(first, 3);
		return -1;	
	}
	return 0;
}
 
static void __exit char_exit(void) /* Destructor */
{
	unregister_chrdev_region(first, 3);
	class_destroy(dcl);
	device_destroy(dcl,first);
	printk(KERN_INFO "Alvida: module unregistered\n");
}

/** @brief A module must use the module_init() module_exit() macros from linux/init.h, which
 *  identify the initialization function at insertion time and the cleanup function (as
 *  listed above)
 */ 
module_init(char_init);
module_exit(char_exit);
 
MODULE_LICENSE("GPL");            ///< The license type -- this affects available functionality
MODULE_AUTHOR("Dharmender Sharma");    ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple Linux char driver for the BBB");  ///< The description -- see modinfo
MODULE_VERSION("0.1");            ///< A version number to inform users
