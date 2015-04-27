#include"header.h"

unsigned char *buffer;
int ii = 1;


int start_func(void);
void end_func(void);
int cdev_initial(void);
int sculldev_initial(void);

int open_func(struct inode *inodep,struct file *filep)
{
	struct Sculldev *lsculldev;
//	int ret;
	#ifdef DEBUG
	printk(KERN_INFO"start:%s\n",__func__);
	#endif
	lsculldev = container_of(inodep->i_cdev,struct Sculldev,c_dev);
	if(!lsculldev)
	{
	#ifdef DEBUG
	printk(KERN_INFO"memory allocation failure\n");
	#endif
	goto OUT;
	}
	filep->private_data = lsculldev;
	if((filep->f_flags & O_ACCMODE) == O_WRONLY)
	{
	}
	if((filep->f_flags & O_ACCMODE) == O_RDONLY)
	{
	}
	if((filep->f_flags & O_ACCMODE) == O_RDWR)
	{
	}
	#ifdef DEBUG
	printk(KERN_INFO"End:%s\n",__func__);
	#endif
	return 0;
OUT:
	#ifdef DEBUG
	printk(KERN_INFO"End E:%s\n",__func__);
	#endif
	return -1;

}



int create_quantum(struct Scullqset *fscullqset,int fnoq)
{
	int i,lnoq,count = 0;
	struct Scullqset * lscullqset;
	lscullqset = fscullqset;
	lnoq = 0;
	#ifdef AVTAR
	printk(KERN_ALERT"Start:%s\n",__func__);
	#endif
	while(lscullqset)
	{
		if(fnoq > quantum_size)
		{
			lnoq = quantum_size;
			fnoq = fnoq - lnoq;
		}
		else
		{
			lnoq = fnoq;
		}
		for(i = 0;i < lnoq;i++)
		{
			lscullqset->data[i] = kmalloc(quantum_size,GFP_KERNEL);
			if(!lscullqset->data[i])
			{
				#ifdef AVTAR
				printk(KERN_ALERT"create_quantum failed\n");
				#endif
				goto OUT;
			}
//			memset(lscullqset->data[i],'\0',quantum_size);
			printk(KERN_ALERT "lscull->data[%d] = %p\n",i,lscullqset->data[i]);
			count++;
		}
		lscullqset = lscullqset->next;
	}
	printk(KERN_INFO "%d quantums created successfully\n",count);

	#ifdef AVTAR
	printk(KERN_ALERT"End:%s\n",__func__);
	#endif
	return 0;
OUT:
	#ifdef AVTAR
	printk(KERN_ALERT"End:%s\n",__func__);
	#endif
	return -1;
}







int create_qset(struct Scullqset *fscullqset,int fnosqs)
{
	int lnoq;

	int i;
	lnoq = qset_size;
	#ifdef AVTAR
	printk(KERN_ALERT"Start:%s\n",__func__);
	#endif
	for(i = 0;i < fnosqs;i++)
	{
		fscullqset->data = kmalloc(sizeof(int) * lnoq,GFP_KERNEL);
		if(!fscullqset->data)
		{
			#ifdef AVTAR
			printk(KERN_ALERT"create_qset failed\n");
			#endif
			goto OUT;
		}
		fscullqset = fscullqset->next;
	}

	#ifdef AVTAR
	printk(KERN_ALERT"End:%s\n",__func__);
	#endif
	return 0;
OUT:
	#ifdef AVTAR
	printk(KERN_ALERT"End:%s\n",__func__);
	#endif
	return -1;
}






struct Scullqset * create_scullqset(int lnosqs)
{
	int i,flag = 0;
	struct Scullqset *fscullqset;
	struct Scullqset *start;
	start = fscullqset = NULL;

	#ifdef AVTAR
	printk(KERN_ALERT"Start:%s\n",__func__);
	#endif
	for(i = 0;i < lnosqs;i++)
	{
		if(!flag)
		{
			start = fscullqset = kmalloc(sizeof(struct Scullqset),GFP_KERNEL);
			if(!fscullqset)
			{
				#ifdef AVTAR
				printk(KERN_ALERT"create_scullqset failed at %d iteration of loop\n",i);
				#endif
				goto OUT;
			}
				#ifdef AVTAR
				printk(KERN_ALERT"start =  %p\n",start);
				#endif
			flag++;
		}
		else
		{
			fscullqset->next = kmalloc(sizeof(struct Scullqset),GFP_KERNEL);
			if(!fscullqset->next)
			{
				#ifdef AVTAR
				printk(KERN_ALERT"create_scullqset failed at %d iteration of loop\n",i);
				#endif
				goto OUT;
			}
				#ifdef AVTAR
				printk(KERN_ALERT"fscullqset->next = %p\n",fscullqset->next);
				#endif
			fscullqset = fscullqset->next;
		}
	
	}
	fscullqset->next = NULL;

	#ifdef AVTAR
	printk(KERN_ALERT"End:%s\n",__func__);
	#endif
	return start;
OUT:
	#ifdef AVTAR
	printk(KERN_ALERT"End:%s\n",__func__);
	#endif
	return NULL;
}


ssize_t scull_read(struct file *filep,char __user *rbuff,size_t size,loff_t *offp)
{
	unsigned char buf[size];
	unsigned char timeout;
	unsigned long len;
//	char dsr;
	int i = 0;
	int ret;
	#ifdef AVTAR
	printk(KERN_ALERT"Start:%s\n",__func__);
	#endif
	#ifdef AVTAR
	printk(KERN_ALERT"minimum size require to store data = %d\t filep->f_pos = %d\n",(int)size,(int)filep->f_pos);
	#endif
	#ifdef AVTAR
	printk(KERN_INFO"no. of bytes to send = %d\n",(int)size);
	#endif
	len = 5;
	timeout = 1;

/*	dsr = inb(PORT_ADDR + 6);
	while((dsr & 0x22) != 0x22)
	{
		wait_event_interruptible_timeout(sculldev->wq,0,timeout);
		dsr = inb(PORT_ADDR + 6);
	}
	outb(0x12,PORT_ADDR + 4);*/

/*	while(1)
	{
		buf[0] = inb(PORT_ADDR + 5);	//LSR = PORT_ADDR + 5
		if((buf[0] & 0x01) == 0x01)
			break;
		wait_event_interruptible_timeout(sculldev->wq,0,timeout);
	}*/
	for(i = 0;i < 5;i++)
      {
		buf[i] = inb(PORT_ADDR + 0);
//		ssleep(0.1);
		printk(KERN_INFO"data received = %c\n",buf[i]);
        }

	ret = copy_to_user(rbuff,buf,len);
	mdelay(500);
//	outb(0x00,PORT_ADDR + 3);
//	outb(0x18,PORT_ADDR + 4);
	#ifdef AVTAR
	printk(KERN_ALERT"End:%s\n",__func__);
	#endif
	return size;
}


ssize_t scull_write(struct file *filep,const char __user *wbuff,size_t size,loff_t *offp)
{
	int ret,i;
	struct Sculldev *lsculldev;
	struct Scullqset * lscullqset;
//	char cts = 0;
	unsigned char timeout = 0;
	#ifdef AVTAR
	printk(KERN_ALERT"Start:%s\n",__func__);
	#endif
	#ifdef AVTAR
	printk(KERN_ALERT"minimum size require to store data = %d\t filep->f_pos = %d\n",(int)size,(int)filep->f_pos);
	#endif
	ret = i = 0;

	buffer = (unsigned char *)kmalloc((size+1),GFP_KERNEL);
	memset(buffer,'\0',strlen(buffer)+1);	

	outb(0x02,PORT_ADDR + 1);


	lsculldev = filep->private_data;
	if(!lsculldev)
	{
		#ifdef AVTAR
		printk(KERN_ALERT"NO sculldev found\n");
		#endif
		goto OUT;
	}
	lscullqset = lsculldev->scullqset;

	/*?????????????????*/
	printk(KERN_INFO"wbuff = %s\n",wbuff);
	ret = copy_from_user(buffer,wbuff,size);
	printk(KERN_INFO"retval = %d\n",ret);

//while(i < 5)
//{
/*	outb(0x01,PORT_ADDR + 4);
	cts = inb(PORT_ADDR + 6);
	while((cts & 0x11) != 0x11)
	{
		printk(KERN_INFO"in cts = %d\n",cts);
		wait_event_interruptible_timeout(lsculldev->wq,0,timeout);
		cts = inb(PORT_ADDR + 6);
	}
	outb(0x10,PORT_ADDR + 4);*/
	timeout = 10;
//	while(i < 1)
//	{
		printk(KERN_INFO"buffer = %s\n",buffer);
		outb(*(buffer+i),PORT_ADDR + 0);
//		ssleep(0.1);
//		i++;
//	}
	#ifdef DEBUG
	printk(KERN_INFO"in write \n");
	#endif
	outb(*(buffer+ii),PORT_ADDR + 0);
	mdelay(500);
	#ifdef DEBUG
	printk(KERN_INFO"still in write \n");
	#endif
//	outb(0x18,PORT_ADDR + 4);
	i = inb(PORT_ADDR + 2);
	#ifdef DEBUG
	printk(KERN_INFO"IIR:%d\n",i);
	#endif
	#ifdef DEBUG
	printk(KERN_INFO"End:%s\n",__func__);
	#endif

	ii = 1;
	return size;
OUT:
	#ifdef DEBUG
	printk(KERN_INFO"End with ERROR:%s\n",__func__);
	#endif
	return -1;
}


int start_func()
{
	int ret;
	#ifdef DEBUG
	printk(KERN_INFO"start:%s\n",__func__);
	#endif
	if(majorno == 0)
	{
		ret = alloc_chrdev_region(&dev,minorno,nod,DEVICE_NAME);
		if(ret < 0)
			{
				#ifdef DEBUG
				printk(KERN_ERR"Error in registring device driver\n");
				#endif
				goto OUT;
			}
		majorno = MAJOR(dev);
		minorno = MINOR(dev);
	}
	else
	{
		dev = MKDEV(majorno,minorno + 1);
		register_chrdev_region(dev,nod,DEVICE_NAME);
	}
	cdev_initial();
	sculldev_initial();
	#ifdef DEBUG
	printk(KERN_INFO"End:%s\n",__func__);
	#endif
	return 0;
OUT:
	#ifdef DEBUG
	printk(KERN_INFO"End with ERROR:%s\n",__func__);
	#endif
	return -1;
}

int cdev_initial()
{
	int i = 0;
	#ifdef DEBUG
	printk(KERN_INFO"START:%s\n",__func__);
	#endif
	sculldev = (struct Sculldev *)kmalloc(sizeof(struct Sculldev) * nod,GFP_KERNEL);
	if(!sculldev)
	{
		#ifdef DEBUG
		printk(KERN_INFO"Memory allocation failure to the sculldev\n");
		#endif
		goto OUT;
	}
	for(i = 0;i < nod;i++)
	{
		dev = MKDEV(majorno,i);
		majorno = MAJOR(dev);
		minorno = MINOR(dev);
		#ifdef DEBUG
		printk(KERN_INFO"MAJOR NO. = %d\tMINOR NO. = %d\n",majorno,minorno);
		#endif
		cdev_init(&sculldev[i].c_dev,&fops);

		sculldev[i].c_dev.owner = THIS_MODULE;
		sculldev[i].c_dev.ops = &fops;
		sculldev[i].c_dev.count = nod;

		cdev_add(&sculldev[i].c_dev,dev,sculldev[i].c_dev.count);
	}
	#ifdef DEBUG
	printk(KERN_INFO"End:%s\n",__func__);
	#endif
	return 1;
OUT:
	#ifdef DEBUG
	printk(KERN_INFO"End E:%s\n",__func__);
	#endif
	return -1;	
}

irqreturn_t interrupt_handler(int irq,void *dev_id)
{
	char iir;
	#ifdef DEBUG
	printk(KERN_INFO"Start:%s\n",__func__);
	#endif
	iir = inb(PORT_ADDR + 2);
	#ifdef DEBUG
	printk(KERN_INFO"IIR:%d\n",iir);
	#endif
	if(*(buffer+ii) == '\0')
	{
		outb(0x00,PORT_ADDR + 1);
		#ifdef DEBUG
		printk(KERN_INFO"End:%s\n",__func__);
		#endif
		return IRQ_HANDLED;
	}
	outb(*(buffer+ii),PORT_ADDR + 0);
	printk(KERN_INFO "buffer + %d = %c\n",ii,*(buffer+ii));
	ii++;
	#ifdef DEBUG
	printk(KERN_INFO"End:%s\n",__func__);
	#endif
	return IRQ_HANDLED;
}


int sculldev_initial()
{
	int i = 0;
	int ret = 0;
	#ifdef DEBUG
	printk(KERN_INFO"START:%s\n",__func__);
	#endif
	for(i = 0;i < nod;i++)
	{
		sculldev[i].qset_size = qset_size;
		sculldev[i].quantum_size = quantum_size;
		sculldev[i].device_size = device_size;
		sculldev[i].scullqset = NULL;
		sculldev[i].wcount = 0;
	}
	init_waitqueue_head(&sculldev->wq);
	if(check_mem_region(PORT_ADDR,8) < 0)
		release_region(PORT_ADDR,8);
	request_region(PORT_ADDR,8,DEVICE_NAME);

	outb(0x80,PORT_ADDR + 3);
	outb(0x0c,PORT_ADDR + 0);
	outb(0x00,PORT_ADDR + 1);
	outb(0x03,PORT_ADDR + 3);
	mdelay(500);

	outb(0x02,PORT_ADDR + 1);
//	outb(0x00,PORT_ADDR + 2);

	outb(0x08,PORT_ADDR + 4);
	ret = request_irq(4,interrupt_handler,IRQF_SHARED,DEVICE_NAME,(void *)"dev");

	#ifdef DEBUG
	printk(KERN_INFO"End:%s\n",__func__);
	#endif
	return 0;
}


void end_func()
{
	int i = 0;
	#ifdef DEBUG
	printk(KERN_INFO"start:%s\n",__func__);
	#endif
	for(i = 0;i < nod;i++)
	{
		cdev_del(&sculldev[i].c_dev);
		unregister_chrdev_region(sculldev[i].c_dev.dev,nod);
	}
//	release_region(PORT_ADDR,8);
	free_irq(4,(void *)"dev");
	#ifdef DEBUG
	printk(KERN_INFO"End:%s\n",__func__);
	#endif

}
module_init(start_func);
module_exit(end_func);
