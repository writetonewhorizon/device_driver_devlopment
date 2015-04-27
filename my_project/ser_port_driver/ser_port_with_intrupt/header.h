#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/wait.h>
#include<linux/sched.h>
#include<linux/netdevice.h>
#include<linux/scc.h>
#include<linux/interrupt.h>

#ifndef AVTAR
#define AVTAR
#endif

#ifndef DEBUG
#define DEBUG 0
#endif


#ifndef DEVICE_NAME
#define DEVICE_NAME "SERIALPORT_AVTAR"
#endif


#ifndef QSET_SIZE
#define QSET_SIZE 8
#endif

#ifndef QUANTUM_SIZE
#define QUANTUM_SIZE 8
#endif


#ifndef DEV
#define DEV 0
#endif

#ifndef DEV_SIZE
#define DEV_SIZE 4096
#endif

#ifndef PORT_ADDR
#define PORT_ADDR 0x03f8
#endif
#ifndef DATA_ADDR
#define DATA_ADDR PORT_ADDR
#endif

#ifndef STATUS_ADDR
#define STATUS_ADDR PORT_ADDR + 1
#endif

#ifndef CONTROL_ADDR
#define CONTROL_ADDR PORT_ADDR + 2
#endif
dev_t dev;
int minorno = 0;
int majorno = 0;
unsigned int nod = 2;
unsigned int qset_size = QSET_SIZE;
unsigned int quantum_size = QUANTUM_SIZE;
unsigned int device_size = DEV_SIZE;
int flag = 0;
/*>>>>>>>>>>>>>>>>>>>file operations<<<<<<<<<<<<<<<<<*/
int open_func(struct inode *, struct file *);
ssize_t scull_write(struct file *,const char __user *,size_t ,loff_t *);
ssize_t scull_read(struct file *,char __user *,size_t ,loff_t *);


struct file_operations fops =
{
	open:open_func,
	write:scull_write,
	read:scull_read
};
/*>>>>>>>>>>>>>>>>>>>file operations<<<<<<<<<<<<<<<<<*/
struct Sculldev
{
	struct Scullqset *scullqset;
	struct cdev c_dev;
	unsigned int qset_size;
	unsigned int quantum_size;
	unsigned int device_size;
	wait_queue_head_t wq;
	int wcount;
}*sculldev;

struct Scullqset
{
	struct Scullqset *next;
	void **data;
};
