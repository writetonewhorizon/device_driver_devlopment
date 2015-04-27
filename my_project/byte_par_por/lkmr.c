#include"header.h"

int creat_quantum(struct Scullqset *fscullqset,int fnoq)
{
	int lv,lnoq;
	#ifdef DEBUG
	printk(KERN_INFO "BEGIN : %s\n",__func__);
	#endif
	while(fnoq)
	{
		if(fnoq>quantum_size)
			lnoq = quantum_size;
		else 
			lnoq = fnoq;
		for(lv=0;lv<lnoq;lv++)
		{
			fscullqset->data[lv] = kmalloc(quantum_size,GFP_KERNEL);
			if(fscullqset->data[lv] == NULL)
			{	
				#ifdef DEBUG
				printk(KERN_ERR "Kmalloc() failed\n");
				#endif
				return -1;
			}
		}
		fscullqset = fscullqset->next;
		fnoq = fnoq-lnoq;

	}
	#ifdef DEBUG
	printk(KERN_INFO "END : %s\n",__func__);
	#endif
	return 0;
}

int creat_qset(struct Scullqset *fscullqset,int fnosqs)
{
	int lv;
	#ifdef DEBUG
	printk(KERN_INFO "BEGIN : %s\n",__func__);
	#endif
	for(lv=0;lv<fnosqs;lv++)
	{
		fscullqset->data = kmalloc(sizeof(int *)*quantum_size,GFP_KERNEL);
		if(fscullqset->data == NULL)
		{	
			#ifdef DEBUG
			printk(KERN_ERR "Kmalloc() failed\n");
			#endif
			return -1;
		}
		fscullqset = fscullqset->next;
	}
	
	#ifdef DEBUG
	printk(KERN_INFO "END : %s\n",__func__);
	#endif
	return 0;
}
struct Scullqset *creat_scullqset(int lnosqs)
{
	int lv,flag;
	struct Scullqset *lscullqset,*start;
	#ifdef DEBUG
	printk(KERN_INFO "BEGIN : %s\n",__func__);
	#endif
	start = NULL;
	flag = 0;
	for(lv=0;lv<lnosqs;lv++)
	{
		if(!flag)
		{
			lscullqset = start = (struct Scullqset *)kmalloc(sizeof(struct Scullqset),GFP_KERNEL);
			if(lscullqset == NULL)
			{
				#ifdef DEBUG
				printk(KERN_ERR "Kmalloc() failed\n");
				#endif	
				return lscullqset;
			}
			flag = 1;
		}
		else
		{
			lscullqset->next = (struct Scullqset *)kmalloc(sizeof(struct Scullqset),GFP_KERNEL);
			if(lscullqset->next == NULL)
			{
				#ifdef DEBUG
				printk(KERN_ERR "Kmalloc() failed \n");
				#endif	
				return lscullqset->next;
			}
			lscullqset = lscullqset->next;
		}
	}
	#ifdef DEBUG
	printk(KERN_INFO "END : %s\n",__func__);
	#endif
	return start;
}
ssize_t par_read(struct file *filep,char __user *buffer,size_t count1,loff_t *loffset)
{
	unsigned long status,data,data1;
	int i,count =0;
	#ifdef DEBUG
	printk(KERN_INFO "BEGIN : %s\n",__func__);
	#endif
	inb(BASE);
	outb(1,BASE+2);

	
	#ifdef DEBUG
	printk(KERN_INFO "DATA : %ld\n",data1);
	#endif
	#ifdef DEBUG
	printk(KERN_INFO "END : %s\n",__func__);
	#endif
	return 0;
}
ssize_t par_write(struct file *filep,const char __user *buffer,size_t count1,loff_t *loffset)
{
	struct Sculldev *lsculldev;
	struct Scullqset *lscullqset;
	int nosqs,noqs,anoq,lnoctw,lnocsw,nob,lnoq,lv,noq;
	int ret,j;
	int i,count=0;
	unsigned long data,lsb,msb,status;
	char buffer1[10];
	#ifdef DEBUG
	printk(KERN_INFO "BEGIN : %s\n",__func__);
	#endif
	lnocsw = nob = lnoctw = nosqs = noqs = anoq = 0;
	lsculldev = filep->private_data;
	if(lsculldev == NULL)
	{
		#ifdef DEBUG
		printk(KERN_ERR "No sculldev found \n");
		#endif
		return -1;
	}
///////////////////////////////////////////////////////////////////////////////////////////////
	

	data = 100;
	lsb = msb = data;
	lsb = lsb<<4;
	lsb = lsb>>4;
	msb = msb>>4;
for(i=0;i<2;i++)
{
again:	status = inb(BASE+1);
	status = status>>7;
	if(status == 0)
	{
		outb(0,BASE+2);
		if(!count)
		{
			outb(lsb,BASE);
			count++;
		}
		else
		{	
			outb(0,BASE+2);
			outb(msb,BASE);

		}
		outb(1,BASE+2);
		sleep(1);
	}
	else
		goto again;
		sleep(1);
}	
outb(0,BASE+2);


//////////////////////////////////////////////////////////////////////////////////////////////
	nosqs = count/(qset_size*quantum_size);
	if(count%(qset_size*quantum_size))
		nosqs++;

	lsculldev->scullqset = creat_scullqset(nosqs);
	if(lsculldev->scullqset == NULL)
	{
		#ifdef DEBUG
		printk(KERN_ERR "creat_scullqset() failed \n");
		#endif
		return -1;
	}

	ret = creat_qset(lsculldev->scullqset,nosqs);
	if(ret<0)
	{
		#ifdef DEBUG
		printk(KERN_ERR "creat_qset() failed \n");
		#endif
		return -1;
	}

	anoq = count/quantum_size;
	if(count%quantum_size)
		anoq++;
	ret = creat_quantum(lsculldev->scullqset,anoq);
	if(ret<0)
	{
		#ifdef DEBUG
		printk(KERN_ERR "creat_quantums() failed \n");
		#endif
		return -1;
	}
	lnoctw = count;
	lscullqset = lsculldev->scullqset;
	noq = anoq;
	while(noq)
	{
		if(noq > quantum_size)
			lnoq = quantum_size;
		else
			lnoq = noq;
		for(lv=0;lv<lnoq;lv++)
		{
			if(lnoctw > quantum_size)
				nob = quantum_size;
			else
				nob = lnoctw;
			ret = copy_from_user(buffer1,buffer,5);
			

//			outb('1',BASE);

			lnocsw += nob - ret;
			lnoctw -= nob + ret;
		}
		noq = noq - lnoq;
		lscullqset = lscullqset->next;
	}

	noq = anoq;
	while(noq)
	{
		if(noq > quantum_size)
			lnoq = quantum_size;
		else
			lnoq = noq;
		for(lv=0;lv<lnoq;lv++)
		{
			if(lnoctw > quantum_size)
				nob = quantum_size;
			else
				nob = lnoctw;
			for(j=0;j<nob;j++)
			{
				outb(*(char *)(lscullqset->data[lv])+j,BASE);
				ssleep(1);
			}
		}
		noq = noq - lnoq;
	}
	#ifdef DEBUG
	printk(KERN_INFO "END : %s\n",__func__);
	#endif
	return lnocsw;
}

int par_open(struct inode *inodep,struct file *filep)
{
	struct Sculldev *lsculldev;
	int ret;
	#ifdef DEBUG
	printk(KERN_INFO "BEGIN : %s\n",__func__);
	#endif
	lsculldev = container_of(inodep->i_cdev,struct Sculldev,c_dev);
	#ifdef DEBUG
	printk(KERN_INFO "Address in open  : %p\n",lsculldev);
	#endif
	filep->private_data = lsculldev;
	#ifdef DEBUG
	printk(KERN_INFO "END : %s\n",__func__);
	#endif
	return 0;
}

void init_scull(void)
{
	#ifdef DEBUG
	printk(KERN_INFO "BEGIN : %s\n",__func__);
	#endif
	
	sculldev->qset_size = qset_size;
	sculldev->quantum_size = quantum_size;
	sculldev->scullqset = NULL;

	#ifdef DEBUG
	printk(KERN_INFO "END : %s\n",__func__);
	#endif
}

int scull_setup_cdev(void)
{
	#ifdef DEBUG
	printk(KERN_INFO "BEGIN : %s\n",__func__);
	#endif
	cdev_init(&sculldev->c_dev,&fops);
	sculldev->c_dev.dev = dev;
	sculldev->c_dev.owner = THIS_MODULE;
	sculldev->c_dev.ops = &fops;
	sculldev->c_dev.count = nod;
	cdev_add(&sculldev->c_dev,dev,nod);
	#ifdef DEBUG
	printk(KERN_INFO "END : %s\n",__func__);
	#endif
	return 0;
}
static int entry_fun(void)
{
	int ret;
	#ifdef DEBUG
	printk(KERN_INFO "BEGIN : %s\n",__func__);
	#endif
	
	ret = alloc_chrdev_region(&dev,minor_no,nod,NAME);
	if(ret<0)
	{
		#ifdef DEBUG
		printk(KERN_ERR "Registeration failed!!!\n");
		#endif
		return -1;
	}

	major_no = MAJOR(dev);
	minor_no = MINOR(dev);
	#ifdef DEBUG
	printk(KERN_INFO "Major no alloted is %d and minor number is %d\n",major_no,minor_no);
	#endif

	sculldev = (struct Sculldev *)kmalloc(sizeof(struct Sculldev)*nod,GFP_KERNEL);
	if(sculldev == NULL)
	{
		#ifdef DEBUG
		printk(KERN_ERR "Kmalloc failed!!!\n");
		#endif
		return -1;
			
	}
	#ifdef DEBUG
	printk(KERN_INFO "Address in entry  : %p\n",sculldev);
	#endif
	
	ret = scull_setup_cdev();
	if(ret<0)
	{
		#ifdef DEBUG
		printk(KERN_ERR "scull_setup_cdev() failed!!!\n");
		#endif
		return -1;
	}

	init_scull();

	ret = check_region(BASE,3);
	if(ret<0)
	{
		#ifdef DEBUG
		printk(KERN_INFO "region busy\n");
		#endif
		release_region(BASE,3);
	}
	request_region(BASE,3,NAME);
	outb(0,BASE+2);
	outb(0,BASE);
	#ifdef DEBUG
	printk(KERN_INFO "END : %s\n",__func__);
	#endif
	return 0;
}

static void exit_fun(void)
{
	#ifdef DEBUG
	printk(KERN_INFO "BEGIN : %s\n",__func__);
	#endif
	release_region(BASE,3);
	cdev_del(&sculldev->c_dev);
	kfree(sculldev);
	unregister_chrdev_region(dev,nod);
	#ifdef DEBUG
	printk(KERN_INFO "END : %s\n",__func__);
	#endif
}
module_init(entry_fun);
module_exit(exit_fun);
