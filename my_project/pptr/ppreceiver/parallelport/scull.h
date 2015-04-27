#include<linux/cdev.h>

int scull_open(struct inode *,struct file *);
int scull_release(struct inode *,struct file *);
ssize_t scull_write(struct file *,const char __user *, size_t, loff_t *);
struct scull_qset
{
void **data;
struct scull_qset *next;
};

struct scull_dev
{
struct scull_qset *scull_Qset;
struct cdev cDev;
int quantum_size;
int qset_size;

int data_size;
int device_size;
};
struct scull_dev *scull_Dev;
struct file_operations fops=
{

open:scull_open,

write:scull_write,
/*
read:scull_read,
*/
release:scull_release

};

