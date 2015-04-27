#include"header.h"
MODULE_LICENSE("GPL");
int x,ret;
		unsigned char ret_intrrupt;
		unsigned char ret_inb;
module_param(nod,int,S_IRUGO);

ssize_t dev_read(struct file *filep,char __user *buffer,size_t count1,loff_t *loffset)
{
	char *ch;
	unsigned char ret_inb;
	#ifdef DEBUG
	printk(KERN_INFO "BEGIN : %s\n",__func__);
	#endif
	ch=(char *)kmalloc(100,GFP_KERNEL);
	while(1)
	{
		ret_inb=inb(BASE+6);
			#ifdef DEFINE
			printk(KERN_INFO " ret_inb  %d",ret_inb);
			#endif
		if((ret_inb &2)==2)
		break;
		mdelay(10);
	}

	outb(2,BASE+4);
	mdelay(10);
	insb(BASE+0,(void *)ch,14);
		#ifdef DEFINE
		printk(KERN_INFO " data read is %s",ch);
		#endif

	#ifdef DEBUG
	printk(KERN_INFO "END : %s\n",__func__);
	#endif
	return ret_inb;
}
ssize_t dev_write(struct file * filep, const char __user *ubuff, size_t count, loff_t * pos)
{
	char ch;
	unsigned char ret_inb;
	#ifdef DEFINE
	printk(KERN_INFO " begin  : %s\n",__func__);
	#endif
	ret=copy_from_user(&ch,ubuff,1);
	if(ret==0)
	{
		#ifdef DEFINE
		printk(KERN_INFO " data written is %c",ch);
		#endif
	}

	else 
	{
		#ifdef DEFINE
		printk(KERN_INFO " remaining bytes are %d\n",ret);
		#endif
	}
				
		
	#ifdef DEFINE
	printk(KERN_INFO " end  : %s\n",__func__);
	#endif
	return ch;
}
int scull_open(struct inode *inodep,struct file *filep)
{
	struct Sculldev *lsculldev;
	#ifdef DEFINE
	printk(KERN_INFO " begin  : %s\n",__func__);
	#endif
	
	#ifdef DEFINE
	printk(KERN_INFO "file open successfully \n");
	#endif
		
	lsculldev=container_of(inodep->i_cdev,struct Sculldev,c_dev);
	filep->private_data=lsculldev;
	if((filep->f_flags & O_ACCMODE)== O_WRONLY)
	{
	/*	recv=scull_trim(lsculldev);
		printk(KERN_INFO"scull_trim call :\n");
		if(recv<0)
		{
			#ifdef DEFINE
			printk(KERN_INFO"scull_trim failed :\n");
			#endif
		}
		else
		{
			#ifdef DEFINE
			printk(KERN_INFO"scull_trim succsfully with no = %d :\n",recv);
			#endif
			
		}*/
			
	}
	#ifdef DEFINE
	printk(KERN_INFO " end  : %s\n",__func__);
	#endif
	return 0; 
}
int scull_release(struct inode *inodep,struct file *filep)
{

	#ifdef DEFINE
	printk(KERN_INFO " begin  : %s\n",__func__);
	#endif

	#ifdef DEFINE
	printk(KERN_INFO "file close successfully \n");
	#endif 
			
	#ifdef DEFINE
	printk(KERN_INFO " end   : %s\n",__func__);
	#endif 
	return 0;
}
void init_scull(void)
{

	#ifdef DEFINE
	printk(KERN_INFO " begin  : %s\n",__func__);
	#endif
	sculldev->quantum_size = quantum_size;
	sculldev->qset_size = qset_size;
	sculldev->device_size = device_size;
	sculldev->data_size = data_size;
	sculldev->scullqset = NULL;
	sculldev->wcount = 0;
	#ifdef DEFINE
	printk(KERN_INFO " end  : %s\n",__func__);
	#endif 

}
void scull_setup_cdev(void)
{
	int lv;
	#ifdef DEFINE
	printk(KERN_INFO " begin  : %s\n",__func__);
	#endif
	for(lv=0;lv<nod;lv++)
	{ 
		dev=MKDEV(majorno,lv);
		cdev_init(&sculldev[lv].c_dev,&fops);
		sculldev[lv].c_dev.owner = THIS_MODULE;
		sculldev[lv].c_dev.ops = &fops;
		sculldev[lv].c_dev.dev = dev;
		sculldev[lv].c_dev.count = nod;
		cdev_add(&sculldev[lv].c_dev,dev,1);
		majorno=MAJOR(dev);
		minorno=MINOR(dev);
		#ifdef DEV_NAME 
		printk(KERN_INFO "device has registored with major number =%d   %d\n",majorno,minorno);
		#endif
	}
	#ifdef DEFINE
	printk(KERN_INFO " end  : %s\n",__func__);
	#endif 
	
}
static int initilization_function(void)
{	
	int recv;
	#ifdef DEFINE
	printk(KERN_INFO " begin  : %s\n",__func__);
	#endif 
	
	if(!majorno)
	{
		recv=alloc_chrdev_region(&dev,minorno,nod,DEV_NAME);
		if(recv<0)
		{
			#ifdef DEFINE
			printk(KERN_INFO"registration failed :\n");
			#endif
		}
			majorno = MAJOR(dev);
			#ifdef DEFINE
			printk(KERN_INFO "device has registored with number %d\n",majorno);
			printk(KERN_INFO "registration completed\n");
			#endif
	}
	
	else
	{
		minorno=minorno+1;
		dev_new=MKDEV( majorno , minorno);
		register_chrdev_region(dev,nod,DEV_NAME);
		printk(KERN_INFO "____________device has registored with number %d\n",dev_new);
		
	}
	printk(KERN_INFO "%p\n",sculldev);
	sculldev = kmalloc(sizeof(struct Sculldev)*nod,GFP_KERNEL);
	if(sculldev>0)
	{
		#ifdef DEFINE
		printk(KERN_INFO "kmalloc successfull\n");
		#endif
	}
		memset(sculldev,'\0',sizeof(struct Sculldev)*nod);
		#ifdef DEFINE
		printk(KERN_INFO "%p\n",sculldev);
		#endif
		scull_setup_cdev();
		init_scull(); 
		ret = check_region(BASE,3);
		if(ret<0)
		{
		#ifdef DEFINE
		printk(KERN_INFO "region busy\n");
		#endif
		release_region(BASE,3);
		}
		request_region(BASE,3,DEV_NAME);
//__________________________________>>>>>>>>>>>>>>>>>to set baud reat<<<<<<<<<<<<<<<<<<__________________________________

		outb(128,BASE+3);
		mdelay(10);
		outb(12,BASE+0);
		mdelay(10);
		outb(0,BASE+1);
		mdelay(10);
		outb(27,BASE+3);
		mdelay(10);
//__________________________________>>>>>>>>>>>>>>>>>to set baud reat<<<<<<<<<<<<<<<<<<__________________________________
		
		outb(15,BASE+2);
		mdelay(10);
			
		#ifdef DEFINE
		printk(KERN_INFO " end  : %s\n",__func__);
		#endif 
	return 0;

}
static void cleanup_function(void)
{
	int lv;
	#ifdef DEFINE
	printk(KERN_INFO " begin  : %s\n",__func__);
	#endif 
	for(lv=0;lv<nod;lv++)
	{
		cdev_del(&sculldev[lv].c_dev);
	}
	kfree(sculldev);
	unregister_chrdev_region(sculldev[0].c_dev.dev,nod);	
	#ifdef DEV_NAME
	printk(KERN_INFO "device has been unregistered \n");
	#endif
	#ifdef DEFINE
	printk(KERN_INFO "end  : %s\n",__func__);
	#endif
}
module_init(initilization_function);
module_exit(cleanup_function);
