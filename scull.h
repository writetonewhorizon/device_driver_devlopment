 #ifndef _SCULL_H_
 #define _SCULL_H_
/*
* Macros to help debugging
*/

#undef PDEBUG             /* undef it, just in case */
#ifdef SCULL_DEBUG
#  ifdef __KERNEL__
/* This one if debugging is on, and kernel space */
#    define PDEBUG(fmt, args...) printk( KERN_DEBUG "scull: " fmt, ## args)
#  else
/* This one for user space */
#    define PDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
#  endif
#else
#  define PDEBUG(fmt, args...) /* not debugging: nothing */
#endif

#undef PDEBUGG
#define PDEBUGG(fmt, args...) /* nothing: it's a placeholder */

#ifndef SCULL_MAJOR
#define SCULL_MAJOR 0   /* dynamic major by default */
#endif

#ifndef SCULL_NR_DEVS
#define SCULL_NR_DEVS 4    /* scull0 through scull3 */
#endif


#endif /* _SCULL_H_ */
#ifndef SCULL_P_NR_DEVS
#define SCULL_P_NR_DEVS 4  /* scullpipe0 through scullpipe3 */
#endif

/*
* The bare device is a variable-length region of memory.
* Use a linked list of indirect blocks.
*
* "scull_dev->data" points to an array of pointers, each
* pointer refers to a memory area of SCULL_QUANTUM bytes.
*
* The array (quantum-set) is SCULL_QSET long.
*/
#ifndef SCULL_QUANTUM
#define SCULL_QUANTUM 4000
#endif

#ifndef SCULL_QSET
#define SCULL_QSET    1000
#endif

/*
* The pipe device is a simple circular buffer. Here its default size
*/
#ifndef SCULL_P_BUFFER
#define SCULL_P_BUFFER 4000
#endif


/*
* Representation of scull quantum sets.
*/
struct scull_qset 
{
	void **data;
	struct scull_qset *next;
};

struct scull_dev 
{
	struct scull_qset *data;  /* Pointer to first quantum set */
	int quantum;              /* the current quantum size */
	int qset;                 /* the current array size */
	unsigned long size;       /* amount of data stored here */
	unsigned int access_key;  /* used by sculluid and scullpriv */
	//struct semaphore sem;     /* mutual exclusion semaphore     */
	struct cdev cdev;         /* Char device structure              */
};

/*
* Prototypes for shared functions
*/

int scull_p_init(dev_t dev);
void scull_p_cleanup(void);
int scull_access_init(dev_t dev);
void scull_access_cleanup(void);

int scull_open(struct inode *inode, struct file *filp);
ssize_t scull_read(struct file *filp, char __user *buf, size_t count,loff_t *f_pos);
ssize_t scull_write(struct file *filp, const char __user *buf, size_t count,loff_t *f_pos);
int scull_release(struct inode *inode, struct file *filp);

struct file_operations scull_fops = 
{
	.owner =    THIS_MODULE,
//	.llseek =   scull_llseek,
	.read =     scull_read,
	.write =    scull_write,
//	.ioctl =    scull_ioctl,
	.open =     scull_open,
	.release =  scull_release,
};

extern int scull_major;     /* main.c */
extern int scull_nr_devs;
extern int scull_quantum;
extern int scull_qset;


//int register_chrdev_region(dev_t first, unsigned int count, char *name);
//int alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, char *name);
//void unregister_chrdev_region(dev_t first, unsigned int count);
//void cdev_init(struct cdev *cdev, struct file_operations *fops);
//int cdev_add(struct cdev *dev, dev_t num, unsigned int count);
//void cdev_del(struct cdev *dev);
//container_of(pointer, container_type, container_field);
//unsigned long copy_to_user(void __user *to, const void *from, unsigned long count);
//unsigned long copy_from_user(void *to, const void __user *from, unsigned long count);
