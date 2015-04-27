#include"header.h"
MODULE_LICENSE("GPL");
int x,ret;
		unsigned char ret_intrrupt;
		unsigned char ret_inb;
module_param(nod,int,S_IRUGO);
int create_quantum(struct Scullqset *fscullqset,int fnoq)
{
	int lnoq,lv;
	int count=0;
	#ifdef DEFINE
	printk(KERN_INFO " begin  : %s\n",__func__);
	#endif
	
	while(fscullqset)
	{	
		if(fnoq>quantum_size)
		{
		lnoq=quantum_size;
		}
		else
		{
		lnoq=fnoq;
		}
		for(lv=0;lv<lnoq;lv++)
		{
			fscullqset->data[lv]=kmalloc(quantum_size,GFP_KERNEL);
			memset(fscullqset->data[lv],'\0',quantum_size);
			#ifdef DEFINE
			printk(KERN_INFO " fscullqset->data = %p   %d\n",fscullqset->data[lv],count);
			#endif
		
		}
		fscullqset=fscullqset->next;
		fnoq=fnoq-lnoq;
	}	
	#ifdef DEFINE
	printk(KERN_INFO " end  : %s\n",__func__);
	#endif
	return 0;

}
int create_qset(struct Scullqset *fscullqset,int fnosqs)
{
	int lv;	
	#ifdef DEFINE
	printk(KERN_INFO " begin  : %s\n",__func__);
	#endif

	for(lv=0;lv<fnosqs;lv++)
	{
		if(!fscullqset)
		{	
			break;
		}
		fscullqset->data=kmalloc(sizeof(int *)*qset_size,GFP_KERNEL);
		memset(fscullqset->data,'\0',sizeof(int *)*qset_size);
		if(fscullqset->data==0)
		{
			
		#ifdef DEFINE
		printk(KERN_INFO " malloc faliure\n");
		#endif
		goto out;
		}
		#ifdef DEFINE
		printk(KERN_INFO " fscullqset->data= %p\n",fscullqset->data);
		#endif
		fscullqset=fscullqset->next;
	}
	#ifdef DEFINE
	printk(KERN_INFO " end  : %s\n",__func__);
	#endif
	return 0;

out:
return -1;		
}
struct Scullqset *create_scullqset(int fnosqs)
{
	int lv,flag;
	struct Scullqset *lscullqset,*start;
	lscullqset = NULL;
	flag=0;
	start=NULL;
	#ifdef DEFINE
	printk(KERN_INFO " begin  : %s\n",__func__);
	#endif
	for(lv=0;lv<fnosqs;lv++)
	{
		if(flag==0)
		{
			start=lscullqset=(struct Scullqset *)kmalloc(sizeof(struct Scullqset),GFP_KERNEL);
			#ifdef DEFINE
			printk(KERN_INFO "----------------------%p\n",lscullqset);
			#endif
			memset(lscullqset,'\0',sizeof(struct Scullqset));
			flag=1;
		}
		else
		{
			
			lscullqset->next=(struct Scullqset *)kmalloc(sizeof(struct Scullqset),GFP_KERNEL);
			lscullqset=lscullqset->next;
			#ifdef DEFINE
			printk(KERN_INFO "lscullqset in write %p\n",lscullqset);
			#endif
			memset(lscullqset,'\0',sizeof(struct Scullqset));
		}
	}
	
	lscullqset->next = NULL;
	#ifdef DEFINE
	printk(KERN_INFO " end  : %s\n",__func__);
	#endif
	return start;

}

ssize_t dev_read(struct file *filep,char __user *buffer,size_t count1,loff_t *loffset)
{
	//char ch;
	#ifdef DEBUG
	printk(KERN_INFO "BEGIN : %s\n",__func__);
	#endif
	
/*	unsigned long status = 0,data;
	if(status==0)
	outb(1,BASE+2);
	data=inb(BASE);
	outb(0,BASE+2);
*/	//outb(32, BASE + 2);
	//ch = inb(BASE);
	//printk(KERN_INFO "recieve char is : %c  %d\n",ch, ch);
	#ifdef DEBUG
//	printk(KERN_INFO "END : %ld\n",data);
	#endif
	#ifdef DEBUG
	printk(KERN_INFO "END : %s\n",__func__);
	#endif
	return 0;
}
irqreturn_t handler_irq(int signum , void *var)
{
	ret_inb = inb(BASE);
	#ifdef DEFINE
	printk(KERN_INFO " data read is  %c %d",ret_inb,ret_inb);
	#endif
	#ifdef DEFINE
	printk(KERN_INFO " signum = %d,argumant var = %s",signum,(char *)var);
	#endif
	return IRQ_HANDLED;
}
ssize_t dev_write(struct file * filep, const char __user *ubuff, size_t count, loff_t * pos)
{
	int noq,nosqs,ret,lv,notb;
	int nobpq=0,loop;
	int nobw=0;
	struct Sculldev *lsculldev;
	struct Scullqset *lscullqset;
	#ifdef DEFINE
	printk(KERN_INFO " begin  : %s\n",__func__);
#endif
	nosqs = noq = 0;
	lsculldev=(struct Sculldev *)filep->private_data;
	lsculldev->wcount=count;
	noq = count/quantum_size;
	if(count % quantum_size)
	noq++;
	#ifdef DEFINE
	printk(KERN_INFO " noq = %d\n",noq);
	#endif
	nosqs = count/(quantum_size * qset_size);
	if(count % (quantum_size * qset_size))
	nosqs++;
	#ifdef DEFINE
	printk(KERN_INFO " nosqs = %d\n",nosqs);
	#endif
	lsculldev->scullqset=create_scullqset(nosqs);
	if(!lsculldev->scullqset)
	{	
		#ifdef DEFINE
		printk(KERN_INFO " create_scullqset faliure\n");
		#endif
	}
	else
	{
		#ifdef DEFINE
		printk(KERN_INFO " create_scullqset successful\n");
		#endif
			
	}
	lscullqset = lsculldev->scullqset;
	ret=create_qset(lscullqset,nosqs );
	if(ret<0)
	{	
		#ifdef DEFINE
		printk(KERN_INFO " create_qset faliure\n");
		#endif
	}
	else
	{
		#ifdef DEFINE
		printk(KERN_INFO " create_qset successful\n");
		#endif
			
	}
	ret=create_quantum(lscullqset,noq);
	if(ret<0)
	{	
		#ifdef DEFINE
		printk(KERN_INFO " create_quantum faliure\n");
		#endif
	}
	else if(ret==noq)
	{
		#ifdef DEFINE
		printk(KERN_INFO " create_quantum successful\n");
		#endif
			
	}
	notb = count;
	while(noq)
	{
		if(noq>quantum_size)
		{
			loop=quantum_size;
		}
		else
		{
			loop=noq;
		}
			for(lv=0;lv<loop;lv++)
			{
				if(notb > quantum_size)
					nobpq=quantum_size;
				else
					nobpq = notb;
				ret=copy_from_user(lscullqset->data[lv],ubuff+nobw,nobpq);
				if(ret==0)
				{
				#ifdef DEFINE
				printk(KERN_INFO " written succesfully %d  %d  %s\n",lv,ret,(char *)lscullqset->data[lv]);
				#endif
				}
				else 
				{
				#ifdef DEFINE
				printk(KERN_INFO " remaining bytes are %d\n",ret);
				#endif
				}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////				  
/*				unsigned long status;
				status=inb(BASE+1);
				if(status==1)
				{
				outb(*((char*)(lscullqset->data[lv])),BASE);
				outb(0,BASE+2);
				}*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//outb(255,0x0378);
				nobw=nobw+(nobpq-ret);
				notb = notb -(nobpq + ret);
				filep->f_pos = nobw;
				#ifdef DEFINE
				printk(KERN_INFO " file_position = %d\n",(int)filep->f_pos);
				#endif
				
			}
		
		lscullqset=lscullqset->next;
		noq=noq-loop;
		
		#ifdef DEFINE
		printk(KERN_INFO " noq= %d\n",noq);
		#endif
	}
	#ifdef DEFINE
	printk(KERN_INFO " end  : %s\n",__func__);
	#endif
	return nobw;
}
int scull_open(struct inode *inodep,struct file *filep)
{
	int recv;	
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
	//ret_inb=(inb(BASE+1) & 64);
	outb(32,BASE+2);     //make bidiractional
	printk("-status:64-----ret_inbs:%d \n",ret_inb); 

	ret_inb=inb(0x0378);
	#ifdef DEFINE
	printk(KERN_INFO "%d \n",ret_inb);
	#endif 
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		ret = check_region(BASE,3);
		if(ret<0)
		{
		#ifdef DEFINE
		printk(KERN_INFO "region busy\n");
		#endif
		release_region(BASE,3);
		}
		request_region(BASE,3,DEV_NAME);
		outb(16,BASE+2);
		ret_intrrupt=request_irq(7,handler_irq,IRQF_SHARED,"Parrallelport","freeargument");
		if(ret_intrrupt==0)
		{
			
			#ifdef DEFINE
			printk(KERN_INFO "irq_request is successful\n");
			#endif
		}
		else
			#ifdef DEFINE
			printk(KERN_INFO "irq_request is failed\n");
			#endif

		//outb(0,BASE+2);
		//outb(0,BASE);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
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
	free_irq(7,"freeargument");
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
