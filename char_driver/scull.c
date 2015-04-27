#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>       /* printk() */
#include <linux/slab.h>         /* kmalloc() */
#include <linux/fs.h>           /* everything.like register */
#include <linux/errno.h>        /* error codes */
#include <linux/types.h>        /* size_t, dev_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h>        /* O_ACCMODE */
#include <linux/seq_file.h>
#include <linux/cdev.h>

#include <asm/uaccess.h>        /* copy_*_user */
#include "scull.h"

MODULE_AUTHOR("Dharmender Sharma");
MODULE_LICENSE("Dual BSD/GPL");

struct scull_dev *scull_devices;

/* Our parameters which can be set at load time. */
int scull_major =   SCULL_MAJOR;
int scull_minor =   0;
int scull_nr_devs = SCULL_NR_DEVS;	/* number of bare scull devices */
int scull_quantum = SCULL_QUANTUM;
int scull_qset =    SCULL_QSET;

/* for proc */
int len,temp;
char *msg;
/*end proc */

//ssize_t read_proc(struct file *filp,char *buf,size_t count,loff_t *offp ) 
ssize_t read_proc(struct file *filp, char __user *buf, size_t count,loff_t *f_pos )
{
	
	printk(KERN_INFO "In proc read");
	//len+= sprintf(buf+len, "Hello proc");
	if(count>temp)
	{
		count=temp;
	}
	temp=temp-count;
	copy_to_user(buf,msg, count);
	if(count==0)
		temp=len;
	return len;
}

//ssize_t write_proc(struct file *filp,const char *buf,size_t count,loff_t *offp)
ssize_t write_proc(struct file *filp, const char __user *buf, size_t count,loff_t *f_pos)
{
	printk(KERN_INFO "In proc write");
	copy_from_user(msg,buf,count);
	len=count;
	temp=len;
	return count;
}

static int scull_create_proc( void )
{
/*static inline struct proc_dir_entry *proc_create(const char *name, umode_t mode,struct proc_dir_entry *parent, 
const struct file_operations *proc_fops)
name: The name of the proc entry
mode: The access mode for proc entry
parent: The name of the parent directory under /proc
proc_fops: The structure in which the file operations for the proc entry will be created. */
	struct proc_dir_entry *proc;
	proc = proc_create("scullmem", 0666 /* default mode */,NULL /* parent dir */, &proc_fops /* proc operation*/);
	if (!proc) 
	{
		printk(KERN_ERR "kaodv_queue: failed to create proc entry\n");
		return -1;
	}
	else
	{
		printk(KERN_ERR "create proc entry successful \n");
	}
	msg=kmalloc(GFP_KERNEL,10*sizeof(char));
	return 0;
}

static void scull_remove_proc( void )
{
    /* no problem if it was not registered */
	remove_proc_entry("scullmem", NULL /* parent dir */);
	printk(KERN_ERR "remove proc entry successful \n");
}

int scull_trim(struct scull_dev *dev)
{
	struct scull_qset *next, *dptr;
	int qset = dev->qset;   /* "dev" is not-null */
	int i;
	printk(KERN_NOTICE "BEGIN >>>>>>%s",__func__ );
	for (dptr = dev->data; dptr; dptr = next) 
	{ /* all the list items */
		if (dptr->data) 
		{
			for (i = 0; i < qset; i++)
				 kfree(dptr->data[i]);
			kfree(dptr->data);
			dptr->data = NULL;
		}
		next = dptr->next;
		 kfree(dptr);
	}
	dev->size = 0;
	dev->quantum = scull_quantum;
	dev->qset = scull_qset;
	dev->data = NULL;
	printk(KERN_NOTICE "END >>>>>>%s",__func__ );
	return 0;
}
/*Though this is always the first operation performed on the device file,If this entry is NULL ,
 opening the device always succeeds.
task performend by this function are:
• Check for device-specific errors (such as device-not-ready or similar hardware problems)
• Initialize the device if it is being opened for the first time
• Update the f_op pointer, if necessary
• Allocate and fill any data structure to be put in filp->private_data
struct file represents an open file in kernel space.
struct file is created by scull_open() function call and is passed to any function that 
operates on the file, until the last close*/
int scull_open(struct inode *inode, struct file *filp)
{
	struct scull_dev *dev; /* device information */
	printk(KERN_NOTICE "BEGIN >>>>>>%s",__func__ );
	
	dev = container_of(inode->i_cdev, struct scull_dev, cdev);
	/*This macro takes a pointer to a field of type container_field , within a structure of
	type container_type , and returns a pointer to the containing structure*/
	filp->private_data = dev; /* for other methods */
	/* now trim to 0 the length of the device if open was write-only */
	if ( (filp->f_flags & O_ACCMODE) == O_WRONLY) 
	{
		//if (down_interruptible(&dev->sem))
		//	return -ERESTARTSYS;
		scull_trim(dev); /* ignore errors */
		//up(&dev->sem);
	}
	return 0;          /* success */
	printk(KERN_NOTICE "END >>>>>>%s",__func__ );
}

/*This operation is invoked when the file structure is being released. Like open,release can be NULL
it perform the following tasks:
• Deallocate anything that open allocated in filp->private_data
• Shut down the device on last close*/
int scull_release(struct inode *inode, struct file *filp)
{
	printk(KERN_NOTICE "BEGIN >>>>>>%s",__func__ );
	
	printk(KERN_NOTICE "END >>>>>>%s",__func__ );
	return 0;
}

struct scull_qset *scull_follow(struct scull_dev *dev, int n)
{
	struct scull_qset *qs = dev->data;
	printk(KERN_NOTICE "BEGIN >>>>>>%s",__func__ );
	/* Allocate first qset explicitly if need be */
	if (! qs) 
	{
		qs = dev->data = kmalloc(sizeof(struct scull_qset), GFP_KERNEL);
		if (qs == NULL)
		return NULL;  /* Never mind */
		memset(qs, 0, sizeof(struct scull_qset));
	}

	/* Then follow the list */
	while (n--) 
	{
		if (!qs->next) 
		{
			qs->next = kmalloc(sizeof(struct scull_qset), GFP_KERNEL);
			if (qs->next == NULL)
			return NULL;  /* Never mind */
			memset(qs->next, 0, sizeof(struct scull_qset));
		}
		qs = qs->next;
		continue;
	}
	printk(KERN_NOTICE "END >>>>>>%s",__func__ );
	return qs;
}

/*Used to retrieve data from the device(kernel space(non swapable) in the driver) and 
copy data to the user space buffer(buf) that is swapable.
A null pointer in this position causes the read system call to fail with -EINVAL (“Invalid argument”). 
A nonnegative return value represents the number of bytes successfully read (the return value is a
“signed size” type, usually the native integer type for the target platform).
filp is the file pointer and count is the size of the requested data
transfer. The buf argument points to the user buffer holding the data to be written or
the empty buffer where the newly read data should be placed. Finally, f_pos is a pointer
to a “long offset type” object that indicates the file position the user is accessing.
The return value for read is interpreted by the calling application program:
• If the value equals the count argument passed to the read system call, the
requested number of bytes has been transferred. This is the optimal case.
• If the value is positive, but smaller than count , only part of the data has been
transferred. This may happen for a number of reasons, depending on the device.
Most often, the application program retries the read. For instance, if you read
using the fread function, the library function reissues the system call until com-
pletion of the requested data transfer.
• If the value is 0 , end-of-file was reached (and no data was read).
• A negative value means there was an error. The value specifies what the error
was, according to <linux/errno.h>. Typical values returned on error include -EINTR
(interrupted system call) or -EFAULT (bad address).*/
ssize_t scull_read(struct file *filp, char __user *buf, size_t count,loff_t *f_pos)
{
	ssize_t retval = 0;	
	struct scull_dev *dev = filp->private_data;
	struct scull_qset *dptr;
	/* the first listitem */
	int quantum = dev->quantum, qset = dev->qset;
	int itemsize = quantum * qset; /* how many bytes in the listitem */
	int item, s_pos, q_pos, rest;
	printk(KERN_NOTICE "BEGIN >>>>>>%s",__func__ );
	//if (down_interruptible(&dev->sem))
	//	return -ERESTARTSYS;
	if (*f_pos >= dev->size)
		goto out;
	if (*f_pos + count > dev->size)
		count = dev->size - *f_pos;
	/* find listitem, qset index, and offset in the quantum */
	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum; q_pos = rest % quantum;
	
	/* follow the list up to the right position (defined elsewhere) */
	dptr = scull_follow(dev, item);
	if (dptr == NULL || !dptr->data || ! dptr->data[s_pos])
		goto out; /* don't fill holes */
	
	/* read only up to the end of this quantum */
	if (count > quantum - q_pos)
	count = quantum - q_pos;
	if (copy_to_user(buf, dptr->data[s_pos] + q_pos, count)) 
	{
		retval = -EFAULT;
		goto out;
	}
	*f_pos += count;
	retval = count;
out:
	//up(&dev->sem);
	printk(KERN_NOTICE "END >>>>>>%s",__func__ );
	return retval;
}

/*read data from the user space buffer and Sends data to the device or driver buffer. 
If NULL , -EINVAL is returned to the program calling the write system call. 
The return value, if nonnegative, represents the number of bytes successfully written.
return value:
• If the value equals count , the requested number of bytes has been transferred.
• If the value is positive, but smaller than count , only part of the data has been
transferred. The program will most likely retry writing the rest of the data.
• If the value is 0 , nothing was written. This result is not an error, and there is no
reason to return an error code. Once again, the standard library retries the call to
write. We’ll examine the exact meaning of this case in Chapter 6, where block-
ing write is introduced.
• A negative value means an error occurred; as for read, valid error values are
those defined in <linux/errno.h>.*/
ssize_t scull_write(struct file *filp, const char __user *buf, size_t count,loff_t *f_pos)
{
	struct scull_dev *dev = filp->private_data;
	struct scull_qset *dptr;
	int quantum = dev->quantum, qset = dev->qset;
	int itemsize = quantum * qset;
	int item, s_pos, q_pos, rest;
	ssize_t retval = -ENOMEM; /* value used in "goto out" statements */
	printk(KERN_NOTICE "BEGIN >>>>>>%s",__func__ );
	//if (down_interruptible(&dev->sem))
	//	return -ERESTARTSYS;
	
	/* find listitem, qset index and offset in the quantum */
	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum; q_pos = rest % quantum;
	
	/* follow the list up to the right position */
	dptr = scull_follow(dev, item);
	if (dptr == NULL)
		goto out;
	if (!dptr->data) 
	{
		dptr->data = kmalloc(qset * sizeof(char *), GFP_KERNEL);
		if (!dptr->data)
			goto out;
		memset(dptr->data, 0, qset * sizeof(char *));
	}
	if (!dptr->data[s_pos]) 
	{
		dptr->data[s_pos] = kmalloc(quantum, GFP_KERNEL);
		if (!dptr->data[s_pos])
			goto out;
	}
	
	/* write only up to the end of this quantum */
	if (count > quantum - q_pos)
		count = quantum - q_pos;
	if (copy_from_user(dptr->data[s_pos]+q_pos, buf, count)) 
	{
		retval = -EFAULT;
		goto out;
	}
	*f_pos += count;
	retval = count;
	/* update the size */
	if (dev->size < *f_pos)
		dev->size = *f_pos;
out:
	//up(&dev->sem);
	printk(KERN_NOTICE "END >>>>>>%s",__func__ );
	return retval;
}

/*
Set up the char_dev structure for this device. 
struct cdev to represent char devices internally.
*/
static void scull_setup_cdev(struct scull_dev *dev, int index)
{
	int err; 
	int devno = MKDEV(scull_major, scull_minor + index);

	printk(KERN_NOTICE "BEGIN >>>>>>%s",__func__ );

	cdev_init(&dev->cdev, &scull_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &scull_fops;
	err = cdev_add (&dev->cdev, devno, 1);
        /* Fail gracefully if need be */
	if (err)
		printk(KERN_NOTICE "Error %d adding scull%d", err, index);

	printk(KERN_NOTICE "END >>>>>>%s",__func__ );
}
int scull_init_module(void)
{
	
	dev_t dev = 0;	/*The minor number portion of dev is often 0 , but there is no requirement to that effect.*/
	int i, result;
	printk(KERN_NOTICE "BEGIN >>>>>>%s",__func__ );
	
	/*
	* Get a range of minor numbers to work with, asking for a dynamic
	* major unless directed otherwise at load time.
	*/
	if (scull_major) 
	{
		dev = MKDEV(scull_major, scull_minor);
		/* If, you have the major and minor numbers and need to turn them into a dev_t */
		printk(KERN_INFO "dev = %d \n", dev);
		result = register_chrdev_region(dev, scull_nr_devs, "scull_driver");
		/* this function is used when you want to get the specific device number passed as a first parameter
		1. dev is behinning device number of the range you would like to allocate'
		2. count is the total number of contiguous device numbers you are requesting.
		3."scull_driver" is the name of the device that should be associated with this number range; it will appear in 
		/proc/devices and sysfs.*/
		if (result==0)
		{
			printk(KERN_INFO "device registeration is successfull \n");
		}
		else
		{
			printk(KERN_INFO "device registeration is unsuccessfull with error %d \n",result);
		}
	} 
	else 
	{
		result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs, "scull_driver");
		/* this function is used to allocate the major number dynamically. dev is an output-only parameter that will,
		 on successful completion, hold the first number in your allocated range. firstminor should be the requested 
		first minor number to use; it is usually 0 .*/
		scull_major = MAJOR(dev);
		printk(KERN_INFO "Major number is %d \n", scull_major);
	}
	if (result < 0) 
	{
		printk(KERN_WARNING "scull: can't get major %d\n", scull_major);
		return result;
	}
	/* 
	* allocate the devices -- we can't have them static, as the number
	* can be specified at load time
	*/
	scull_devices = kmalloc(scull_nr_devs * sizeof(struct scull_dev), GFP_KERNEL);
	if (!scull_devices) 
	{
		result = -ENOMEM;
		printk(KERN_INFO "kmalloc failed \n");
		goto fail;  /* Make this more graceful */
	}
	memset(scull_devices, 0, scull_nr_devs * sizeof(struct scull_dev));
	/* Initialize each device. */
	for (i = 0; i < scull_nr_devs; i++) 
	{
		scull_devices[i].quantum = scull_quantum;
		scull_devices[i].qset = scull_qset;
		scull_setup_cdev(&scull_devices[i], i);
	}
	scull_create_proc();
	
fail:
	printk(KERN_NOTICE "END >>>>>>%s",__func__ );
	return result;
}
/*
* The cleanup function is used to handle initialization failures as well.
* Thefore, it must be careful to work correctly even if some of the items
* have not been initialized
*/

void scull_cleanup_module(void)
{
	
	dev_t devno = MKDEV(scull_major, scull_minor);	
	int i;

	printk(KERN_NOTICE "BEGIN >>>>>>%s",__func__ );
	scull_remove_proc();
	/* Get rid of our char dev entries */
	if (scull_devices) 
	{
		for (i = 0; i < scull_nr_devs; i++) 
		{
			scull_trim(scull_devices + i);
			cdev_del(&scull_devices[i].cdev);
		}
		kfree(scull_devices);
	}

	/* cleanup_module is never called if registering failed */
	unregister_chrdev_region(devno, scull_nr_devs);
	/* and call the cleanup functions for friend devices */
//	scull_p_cleanup();
//	scull_access_cleanup();
	
	printk(KERN_NOTICE "END >>>>>>%s",__func__ );

}

module_init(scull_init_module);
module_exit(scull_cleanup_module);
