//#include</usr/src/kernels/linux-3.8.6/include/linux/module.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/init.h>
#include<linux/moduleparam.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<asm-generic/uaccess.h>
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

MODULE_LICENSE("GPL");

#ifndef DEBUG
#define DEBUG
#endif

#ifndef D_NAME
#define D_NAME "My_ch_Driver"
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

unsigned long long wj_start,wj_end,rj_start,rj_end;
int flag,flag1;

void set_sculldev(void);
void init_sculldev(void);
int my_open(struct inode *, struct file *);
int my_close(struct inode *, struct file *);
int my_write(struct file *, const char __user *, size_t, loff_t *);
int my_read(struct file *, char __user *, size_t, loff_t *);
//long ioctl_op(struct file *, unsigned int, unsigned long);
loff_t my_lseek(struct file *, loff_t, int);
void set_2_default(void);

const struct file_operations f_op=
{
	.open = my_open,
	.release = my_close,
	.write = my_write,
	.read = my_read,
	.llseek = my_lseek,
//	.unlocked_ioctl = ioctl_op
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
	struct semaphore sem;
	struct completion comp;
	struct timer_list soft_intrupt;
	int quantum_size;
	int qset_size;
	int data_size;
	int device_size;
	int wcount;
	int open_count;
	wait_queue_head_t rd_queue,wr_queue;
};

struct proc_dir_entry *proc_dir;
	spinlock_t my_lock;

int scull_trim(struct ScullDev *);
struct ScullDev *sculldev;
struct ScullQset * create_scullqset(int);
struct proc_dir_entry dir_proc;
int create_qset(struct ScullQset *,int);
int create_quantums(struct ScullQset *,int,int);
int scull_deallocate(struct ScullQset *);
int read_sculldev(char *, char **, off_t, int, int *, void *);
int count_jiffie(char *, char **, off_t, int, int *, void *);
int add_delay(char *, char **, off_t, int, int *, void *);
void intrupt_handler(unsigned long);


int majorno = MAJOR_NO;
int minorno = MINOR_NO;
int nod = NOD;
int open_count = OPEN_COUNT;

int quantum_size = QUANTUM_SIZE;
int qset_size = QSET_SIZE;
int data_size = DATA_SIZE;
int device_size = DEVICE_SIZE;

struct timespec nano_sec_start,nano_sec_end;
struct timespec nano_sec_rstart,nano_sec_rend;
struct timeval micro_sec;

dev_t dev;
