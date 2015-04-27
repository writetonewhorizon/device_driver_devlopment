#include<linux/module.h>
#include<linux/init.h>
#include<linux/slab.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/delay.h>
#include<linux/uaccess.h>
#include<linux/ioport.h>
#include<linux/parport.h>
#include<linux/parport_pc.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("DHARMENDER SHARMA");


#ifndef DEBUG
#define DEBUG
#endif


#ifndef NAME
#define NAME "Parallel Port Driver"
#endif
#ifndef QUANTUM_SIZE
#define QUANTUM_SIZE 8
#endif
#ifndef QSET_SIZE
#define QSET_SIZE 8
#endif
#ifndef NOD
#define NOD 1
#endif
#ifndef MAJORNO
#define MAJORNO 0
#endif
#ifndef MINORNO
#define MINORNO 0
#endif
#ifndef BASE
#define BASE 0x378
#endif
#ifndef MAJORNO
#define MAJORNO 0
#endif


int quantum_size = QUANTUM_SIZE;
int qset_size = QSET_SIZE;
int nod = NOD;
int major_no = MAJORNO;
int minor_no = MINORNO;

dev_t dev;
struct Scullqset{
	struct Scullqset *next;
	void **data;
};
struct Sculldev{
	struct cdev c_dev;
	struct Scullqset *scullqset;
	int qset_size;
	int quantum_size;
}*sculldev;
ssize_t par_write(struct file *,const char __user *,size_t,loff_t *);
ssize_t par_read(struct file *,char __user *,size_t,loff_t *);
int par_open(struct inode *,struct file *);
struct file_operations fops=
{
	write:par_write,
	read:par_read,
	open: par_open
};
