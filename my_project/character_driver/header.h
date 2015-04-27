#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/init.h>
#include<linux/moduleparam.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/sched.h>
#include<linux/wait.h>
#include<linux/interrupt.h>

MODULE_LICENSE("GPL");

#ifndef DEBUG
#define DEBUG
#endif

#ifndef D_NAME
#define D_NAME "MY_Serial_Driver"
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

#ifndef RX_PORT
#define RX_PORT 0x03f8
#endif

#ifndef TX_PORT
#define TX_PORT 0x03f8
#endif

#ifndef DLL
#define DLL 0x03f8
#endif

#ifndef DLM
#define DLM 0x03f9
#endif

#ifndef IER
#define IER 0x03f9
#endif

#ifndef IIR
#define IIR 0x03fa
#endif

#ifndef FCR
#define FCR 0x03fa
#endif

#ifndef LCR
#define LCR 0x03fb
#endif

#ifndef MCR
#define MCR 0x03fc
#endif

#ifndef LSR
#define LSR 0x03fd
#endif

#ifndef MSR
#define MSR 0x03fe
#endif

void set_sculldev(void);
void init_sculldev(void);

int my_open(struct inode *, struct file *);
int my_close(struct inode *, struct file *);
int my_write(struct file *, const char __user *, size_t, loff_t *);
int my_read(struct file *, char __user *, size_t, loff_t *);

loff_t my_lseek(struct file *, loff_t, int);

const struct file_operations f_op=
{
	.open = my_open,
	.release = my_close,
	.write = my_write,
	.read = my_read,
	.llseek = my_lseek,
};

struct ScullQset
{
	struct ScullQset *next;
	void **data;
};

struct ScullDev
{
	struct cdev c_dev;
	struct ScullQset *scullqset;
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
int byte_transfer(struct ScullDev *);

irqreturn_t rx_handler(int ,void *);
irqreturn_t tx_handler(int ,void *);

wait_queue_head_t wr_wait;
spinlock_t my_lock;

int majorno = MAJOR_NO;
int minorno = MINOR_NO;
int nod = NOD;
int open_count = OPEN_COUNT;

int quantum_size = QUANTUM_SIZE;
int qset_size = QSET_SIZE;
int data_size = DATA_SIZE;
int device_size = DEVICE_SIZE;

dev_t dev;
