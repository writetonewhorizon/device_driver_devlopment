#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kdev_t.h>
#include<linux/slab.h>
#include<linux/cdev.h>
#include<linux/moduleparam.h>
#include<asm/uaccess.h>
#include<linux/fs.h>
#include<linux/delay.h>
#ifndef DEFINE
#define DEFINE
#endif

#ifndef DEV_NAME
#define DEV_NAME  "Dharmender's driver"
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

#ifndef QUANTUM_SIZE
#define QUANTUM_SIZE 8
#endif

#ifndef QSET_SIZE
#define QSET_SIZE 8
#endif

#ifndef DEVICE_SIZE
#define DEVICE_SIZE 4096
#endif

#ifndef DATA_SIZE
#define DATA_SIZE 0
#endif

#ifndef BASE
#define BASE 0x3f8
#endif

int majorno = MAJOR_NO;
dev_t dev,dev_new;
int minorno = MINOR_NO;
int nod = NOD;
int qset_size = QSET_SIZE;
int quantum_size = QUANTUM_SIZE;
int device_size = DEVICE_SIZE;
int data_size = DATA_SIZE;
int scull_open(struct inode*,struct file*);
int scull_release(struct inode*,struct file*);
ssize_t dev_write(struct file *, const char __user *, size_t, loff_t *);
struct resource *lregion;
ssize_t dev_read(struct file *,char __user *,size_t,loff_t *);
struct file_operations fops=
{
	open:scull_open,
	release:scull_release,
	write:dev_write,
	read:dev_read
};
struct Sculldev
{
	struct Scullqset *scullqset;
	struct cdev c_dev;
	int qset_size;
	int quantum_size;
	int device_size;
	int data_size;
	int wcount;

}*sculldev;
struct Scullqset
{
		struct Scullqset *next;
		void **data;
	
};

