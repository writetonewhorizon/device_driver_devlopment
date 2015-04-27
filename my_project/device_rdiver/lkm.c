#include"header.h"
MODULE_LICENSE("GPL");
module_param(nod,int,S_IRUGO);
loff_t scull_llseek(struct file *filep, loff_t offset, int whence)
{
	
	#ifdef DEFINE
	printk(KERN_INFO " begin  : %s\n",__func__);
	#endif
	
	#ifdef DEFINE
	printk(KERN_INFO " offset= %d and whence =  %d\n",(int)offset,whence);
	#endif
	switch(whence)
	{
		case 0:
			filep->f_pos = offset;
			#ifdef DEFINE
			printk(KERN_INFO " new_position0 = %d\n  ",(int)filep->f_pos);
			#endif	
			break;
		case 1:
			filep->f_pos = filep->f_pos+offset;
			#ifdef DEFINE
			printk(KERN_INFO " new_position1=  %d  \n",(int)filep->f_pos);
			#endif
			break;
		case 2:
			filep->f_pos = data_size+offset;
			#ifdef DEFINE
			printk(KERN_INFO " new_position2 = %d  \n",(int)filep->f_pos);
			#endif
			break;

	}
	#ifdef DEFINE
	printk(KERN_INFO " end  : %s\n",__func__);
	#endif
	return filep->f_pos;
}

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

ssize_t dev_read (struct file * filep, char __user * ubuff, size_t count, loff_t * pos)
{
	int lv,noq,loop,ret,notb,sqsno,sqno,bno,nobw,nobpq,seek,i;
	struct Sculldev *lsculldev;
	struct Scullqset *lscullqset,*tscullqset;
	#ifdef DEFINE
	printk(KERN_INFO " begin  : %s\n",__func__);
	#endif
	#ifdef DEFINE
	printk(KERN_INFO " filep->f_pos = %d\n",(int)filep->f_pos);
	#endif
	loop=nobw=nobpq=bno=sqno=notb=sqsno=0;
	seek=(int)filep->f_pos;
	#ifdef DEFINE
	printk(KERN_INFO " seek = %d \n",seek);
	#endif
	#ifdef DEFINE
	printk(KERN_INFO " count = %d \n",(int)count);
	#endif
	
	noq=count/quantum_size;
	if(count%quantum_size)
		noq++;
	#ifdef DEFINE
	printk(KERN_INFO " noq = %d\n",noq);
	#endif
	lsculldev = (struct Sculldev *)filep->private_data;
	if(!sculldev)
	{
		#ifdef DEFINE
		printk(KERN_INFO "error\n");
		#endif
	}
	if(!lsculldev->scullqset)
	{
		#ifdef DEFINE
		printk(KERN_INFO "no scullqset\n");
		#endif
	}
	if(!lsculldev->scullqset->data)
	{
		#ifdef DEFINE
		printk(KERN_INFO "no data to read\n");
		#endif
	}
	
	lscullqset=lsculldev->scullqset;
	sqsno = seek / (quantum_size * qset_size);
	if(sqsno)
	{
	for(i=0;i<sqsno;i++)
	{
		if(lscullqset->next)
		{
		lscullqset = lscullqset->next;
		#ifdef DEFINE
		printk(KERN_INFO " lscullqset = %p\n",lscullqset);
		#endif
		}
		else
		break;
	}
	}
	#ifdef DEFINE
	printk(KERN_INFO " sqsno = %d\n",sqsno);
	#endif
	sqno = seek / quantum_size;
	sqno = sqno - sqsno*quantum_size;
	#ifdef DEFINE
	printk(KERN_INFO " qsno = %d\n",sqno);
	#endif
	bno = seek % quantum_size;
	#ifdef DEFINE
	printk(KERN_INFO " bno = %d\n",bno);
	#endif
	notb = count;
	#ifdef DEFINE
	printk(KERN_INFO " filep->f_pos = %d\n",(int)filep->f_pos);
	#endif

	#ifdef DEFINE
	printk(KERN_INFO " notb = %d\n",notb);
	#endif

	while(lscullqset)
	{
		if(noq>quantum_size)
		{
			loop = quantum_size;
			#ifdef DEFINE
			printk(KERN_INFO " loop = %d\n",loop);
			#endif
		}
		else
		{
			loop=noq;
		}
	
		for(lv=sqno;lv<loop;lv++)
		{
			if(notb > quantum_size)
				nobpq=quantum_size;
			else
				nobpq = notb;
			
			ret=copy_to_user(ubuff+nobw,lscullqset->data[lv]+bno,nobpq-bno);
			if(ret==0)
			{
			#ifdef DEFINE
			printk(KERN_INFO " read succesfully %d  %d  %s\n",lv,ret,(char *)lscullqset->data[lv]+bno);
			#endif
			}
			else 
			{
			#ifdef DEFINE
			printk(KERN_INFO " remaining bytes are %d\n",ret);
			#endif
			}
		/*	lscullqset->data[lv]=NULL;
			kfree(lscullqset->data[lv]);
			#ifdef DEFINE
			printk(KERN_INFO " lscullqset->data[lv]= %p\n",lscullqset->data[lv]);
			#endif*/
			
			notb = notb - nobpq -bno + ret;
			#ifdef DEFINE
			printk(KERN_INFO " notb= %d\n",notb);
			#endif
			nobw=nobw + nobpq - bno - ret;
			#ifdef DEFINE
			printk(KERN_INFO " nobw= %d\n",nobw);
			#endif
			bno=0;
		}
			sqno=0;
			noq = noq - loop ;		
		/*	lscullqset->data=NULL;
			kfree(lscullqset->data);
			#ifdef DEFINE
			printk(KERN_INFO " lscullqset->data= %p\n",lscullqset->data);
			#endif*/
			if(!lscullqset->next)
			{
				break;
			}
			tscullqset = lscullqset->next;
		/*	lscullqset=NULL;
			kfree(lscullqset);
			#ifdef DEFINE
			printk(KERN_INFO " lscullqset= %p\n",lscullqset);
			#endif*/
			lscullqset=tscullqset;
	}
	#ifdef DEFINE
	printk(KERN_INFO " end  : %s\n",__func__);
	#endif
	return nobw;

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
int scull_trim(struct Sculldev *lsculldev)
{
	int noq,loop,lv;
	struct Scullqset *lscullqset,*tscullqset;
	#ifdef DEFINE
	printk(KERN_INFO " begin  : %s\n",__func__);
	#endif

	lscullqset=lsculldev->scullqset;
	#ifdef DEFINE
	printk(KERN_INFO "lsculldev->wcount = %d\n",lsculldev->wcount);
	#endif
	noq = lsculldev-> wcount/quantum_size;	
	if(lsculldev->wcount % quantum_size)
	noq++;
	#ifdef DEFINE
	printk(KERN_INFO " noq =%d \n",noq);
	#endif
	while(noq)
	{
		if(noq > quantum_size)
		{
			loop = quantum_size;
		}
		else
		{
			loop = noq;
		}
		for(lv=0;lv<loop;lv++)
		{
			kfree(lscullqset->data[lv]);
			lscullqset->data[lv]=NULL;
			#ifdef DEFINE
			printk(KERN_INFO " lscullqset->data[lv]= %p\n",lscullqset->data[lv]);
			#endif
		}
		noq=noq-loop;
		kfree(lscullqset->data);
		lscullqset->data = NULL;
		#ifdef DEFINE
		printk(KERN_INFO " lscullqset->data= %p\n",lscullqset->data);
		#endif
		if(!lscullqset->next)
		{
			break;
		}
		tscullqset = lscullqset->next;
		kfree(lscullqset);
		lscullqset = NULL;
		#ifdef DEFINE
		printk(KERN_INFO " lscullqset= %p\n",lscullqset);
		#endif
		lscullqset = tscullqset;
		#ifdef DEFINE
		printk(KERN_INFO "************* lscullqset= %p\n",lscullqset);
		#endif
		#ifdef DEFINE
		printk(KERN_INFO "************* lscullqset->data= %p\n",lscullqset->data);
		#endif

	}
	#ifdef DEFINE
	printk(KERN_INFO " end  : %s\n",__func__);
	#endif
	return 0;

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
		printk(KERN_INFO"scull_trim call :\n");
		recv=scull_trim(lsculldev);
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
			
		}
			
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
