//int register_chrdev_region(dev_t, unsigned, const char *);
int alloc_chrdev_region(dev_t *first, unsigned int firstminor, unsigned int cnt, char *name);i
void unregister_chrdev_region(dev_t, unsigned);
void cdev_init(struct cdev *, const struct file_operations *);
int cdev_add(struct cdev *, dev_t, unsigned);
