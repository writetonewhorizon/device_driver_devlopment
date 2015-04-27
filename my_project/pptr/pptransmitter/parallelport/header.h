#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/kdev_t.h>
#include<linux/semaphore.h>
#include<linux/completion.h>
#include<linux/spinlock.h>
#include<linux/proc_fs.h>
#include<linux/jiffies.h>
#include<linux/time.h>
#include<linux/ioport.h>
#include<asm/msr.h>
#include<linux/io.h>
#include<linux/delay.h>
#include<linux/interrupt.h>

//#include<asm-generic/io.h>
//#include<asm-generic/param.h>
//#include<asm-generic/ioctl.h>
//#include<asm-generic/uaccess.h>

#include"scull.h"
#define START 0x0378; 
//#define END 038a; 
#define DEVICE_NAME "parallelport"
#define MAJORNO 0
#define MINORNO 0
#define CM 1
#define DATA_SIZE 0
#define DEVICE_SIZE 4096 
#define QUANTUM_SIZE 8 
#define QSET_SIZE 8

int data_size=DATA_SIZE;
int device_size=DEVICE_SIZE;

dev_t dev;
int cm=CM;
static int majorno=MAJORNO;
static int minorno=MINORNO;
int quantum_size=QUANTUM_SIZE;
int qset_size=QSET_SIZE;
int  creat_qset(struct scull_qset *);
int creat_quantum(struct scull_qset *, int );
struct scull_qset * creat_scullqset();

int driver_memory(void);



