/* Our First Driver code 
*
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
//#define  DEVICE_NAME "ebbchar"    ///< The device will appear at /dev/ebbchar using this value
//#define  CLASS_NAME  "ebb"        ///< The device class -- this is a character device driver
#include <linux/cdev.h>
static dev_t first; 		// Global variable for the first device number
static struct cdev c_dev; 	// Global variable for the character device structure
static struct class *cl; 	// Global variable for the device class

static int my_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Driver: open()\n");
	return 0;
}
static int my_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Driver: close()\n");
	return 0;
}
static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Driver: read()\n");
	return 0;
}
static ssize_t my_write(struct file *f, const char __user *buf,size_t len, loff_t *off)
{
	printk(KERN_INFO "Driver: write()\n");
	return 0;
}
static struct file_operations char_fops = {
  .owner = THIS_MODULE,
  .open = my_open,
  .release = my_close,
  .read = my_read,
  .write = my_write
};

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
	if ( (cl = class_create(THIS_MODULE, "chardev")) == NULL ) {
		printk(KERN_INFO " class chardev is not created successfully\n");
		unregister_chrdev_region(first, 3);
		return -1;
	}
	/*to create character "mynull" node under /dev */
	if (device_create(cl, NULL, first, NULL, "mynull") == NULL)
	{
		printk(KERN_INFO " device  is not created successfully\n");
		class_destroy(cl);
		unregister_chrdev_region(first, 3);
		return -1;
	}

	cdev_init(&c_dev, &char_fops);
	if (cdev_add(&c_dev, first, 3) == -1)
	{
		printk(KERN_INFO " device  is not added successfully\n");
		class_destroy(cl);
		device_destroy(cl,first);
		unregister_chrdev_region(first, 3);
		return -1;	
	}
	return 0;
}
 
static void __exit char_exit(void) /* Destructor */
{
	unregister_chrdev_region(first, 3);
	class_destroy(cl);
	device_destroy(cl,first);
	printk(KERN_INFO "Alvida: module unregistered\n");
}
 
module_init(char_init);
module_exit(char_exit);
 
MODULE_LICENSE("GPL");            ///< The license type -- this affects available functionality
MODULE_AUTHOR("Dharmender Sharma");    ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple Linux char driver for the BBB");  ///< The description -- see modinfo
MODULE_VERSION("0.1");            ///< A version number to inform users
