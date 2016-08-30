//int register_chrdev_region(dev_t, unsigned, const char *);
int alloc_chrdev_region(dev_t *first, unsigned int firstminor, unsigned int cnt, char *name);i
void unregister_chrdev_region(dev_t, unsigned);
void cdev_init(struct cdev *, const struct file_operations *);
int cdev_add(struct cdev *, dev_t, unsigned);

// The prototype fileoperation functions for the character driver -- must come before the struct definition
static int     dev_open(struct inode *, struct file *);
static int     dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

/** @brief Devices are represented as file structure in the kernel. The file_operations structure from
 *  /linux/fs.h lists the callback functions that you wish to associated with your file operations
 *  using a C99 syntax structure. char devices usually implement open, read, write and release calls
 */
static struct file_operations fops =
{
   .open = dev_open,
   .read = dev_read,
   .write = dev_write,
   .release = dev_release,
};

/*dev_open(): Called each time the device is opened from user space.
dev_read(): Called when data is sent from the device to user space.
dev_write(): Called when data is sent from user space to the device.
dev_release(): Called when the device is closed in user space.
*/
