//#include</usr/src/kernels/linux-3.8.6/include/linux/module.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/init.h>
#include<linux/moduleparam.h>
#include<linux/cdev.h>
#include<linux/slab.h>
//#include<asm-generic/uaccess.h>
#include<linux/semaphore.h>
#include<linux/proc_fs.h>
#include<linux/jiffies.h>
#include<linux/time.h>
//#include<asm/msr.h>
#include<linux/sched.h>
#include<linux/wait.h>
#include<linux/hardirq.h>
#include<linux/delay.h>
#include<linux/spinlock.h>
#include<linux/usb.h>

#ifndef DEBUG
#define DEBUG
#endif

#ifndef D_NAME
#define D_NAME "USB_ch_Driver"
#endif

#ifndef MAJOR_NO
#define MAJOR_NO 0
#endif

#ifndef MINOR_NO
#define MINOR_NO 0
#endif

#ifndef NOD
#define NOD 1
#endif

#ifndef DEVICE_SIZE
#define DEVICE_SIZE 4096
#endif

#ifndef QUANTUM_SIZE
#define QUANTUM_SIZE 8
#endif

#ifndef QSET_SIZE
#define QSET_SIZE 8
#endif

#ifndef DATA_SIZE
#define DATA_SIZE 0
#endif

#ifndef OPEN_COUNT
#define OPEN_COUNT 0
#endif

MODULE_LICENSE("GPL");

unsigned long long wj_start,wj_end,rj_start,rj_end;
int flag,flag1;
int lv;

void set_sculldev(void);
void init_sculldev(void);
int my_open(struct inode *, struct file *);
int my_close(struct inode *, struct file *);
int my_write(struct file *, const char __user *, size_t, loff_t *);
int my_read(struct file *, char __user *, size_t, loff_t *);

const struct file_operations f_op=
{
	.open = my_open,
	.release = my_close,
	.write = my_write,
	.read = my_read,
};

struct ScullQset
{
	struct ScullQset *next;
	void **data;
};

struct ScullDev
{
	struct ScullQset *scullqset;
	struct usb_interface *interface;
	struct usb_endpoint_descriptor my_end_desc[3];
	struct usb_device *usb_dev;
	struct cdev c_dev;
	int quantum_size;
	int qset_size;
	int data_size;
	int device_size;
	int wcount;
	int open_count;
};

int scull_trim(struct ScullDev *);
struct ScullDev *sculldev;
struct ScullQset * create_scullqset(int);
int create_qset(struct ScullQset *,int);
int create_quantums(struct ScullQset *,int,int);
int scull_deallocate(struct ScullQset *);

int majorno = MAJOR_NO;
int minorno = MINOR_NO;
int nod = NOD;
int open_count = OPEN_COUNT;

int quantum_size = QUANTUM_SIZE;
int qset_size = QSET_SIZE;
int data_size = DATA_SIZE;
int device_size = DEVICE_SIZE;

dev_t dev;
