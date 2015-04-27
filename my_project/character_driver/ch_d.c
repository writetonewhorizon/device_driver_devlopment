#include"header.h"

module_param(nod,int,S_IRUGO);

static int start_func(void)
{
	int ret;

	#ifdef DEBUG
	printk(KERN_ALERT"Begin %s nod = %d\n",__func__,nod);
	#endif

		if(!majorno)
		{
			ret = alloc_chrdev_region(&dev,minorno,nod,D_NAME);

			if(ret)
			{
				#ifdef DEBUG
				printk(KERN_ALERT"Registration Failed for dev_id %d\n",dev);
				#endif
				return -1;
			}

			#ifdef DEBUG
			printk(KERN_ALERT"%s registerd with dev_id %d\n",D_NAME,dev);
			#endif
			majorno = MAJOR(dev);
		}
		else
		{
			dev = MKDEV(majorno,++minorno);
//			ret = register_chrdev_region(dev,nod,D_NAME);
			
//			if(ret<0)
//			{
//				printk(KERN_ALERT"Registration Failed for dev_id %d\n",dev);
		//		return -1;
		//	}
		}

	set_sculldev();
	init_sculldev();
	
	#ifdef DEBUG
	printk(KERN_ALERT"END %s\n",__func__);
	#endif

	return 0;
}

static void end_func(void)
{
	int lv;
	#ifdef DEBUG
	printk(KERN_ALERT"Begin %s\n",__func__);
	#endif

	for(lv=0; lv<nod; lv++)
	{
		cdev_del(&(sculldev+lv)->c_dev);
		unregister_chrdev_region((sculldev+lv)->c_dev.dev,nod);
		#ifdef DEBUG
		printk(KERN_ALERT"%s unregisterd with major no %d\n",D_NAME,majorno);
		#endif	
	}
	kfree(sculldev);
	#ifdef DEBUG
	printk(KERN_ALERT"END %s\n",__func__);
	#endif
}

void set_sculldev(void)
{
	int lv;
	#ifdef DEBUG
	printk(KERN_ALERT"Begin %s\n",__func__);
	#endif

	sculldev = kmalloc(sizeof(struct ScullDev) * nod, GFP_KERNEL);
	memset(sculldev,'\0',sizeof(struct ScullDev)*nod);
	
	for(lv=0; lv<nod; lv++)
	{
		dev = MKDEV(majorno,lv);
		cdev_init(&(sculldev+lv)->c_dev,&f_op);	
		(sculldev+lv)->c_dev.owner = THIS_MODULE;
		(sculldev+lv)->c_dev.ops = &f_op;
		(sculldev+lv)->c_dev.dev = dev;
		(sculldev+lv)->c_dev.count = nod;
		cdev_add(&(sculldev+lv)->c_dev,dev,nod);
	}
 
	#ifdef DEBUG
	printk(KERN_ALERT"END sculldev is %p   %s\n",sculldev,__func__);
	#endif

}

void init_sculldev(void)
{
	int lv;

	#ifdef DEBUG
	printk(KERN_ALERT"Begin %s\n",__func__);
	#endif
	
	for(lv=0; lv<nod; lv++)
	{
		(sculldev+lv)->quantum_size = QUANTUM_SIZE;
		(sculldev+lv)->qset_size = QSET_SIZE;
		(sculldev+lv)->device_size = DEVICE_SIZE;
		(sculldev+lv)->data_size = DATA_SIZE;
		(sculldev+lv)->open_count = OPEN_COUNT;
	}

	#ifdef DEBUG
	printk(KERN_ALERT"END %s\n",__func__);
	#endif
}

int my_open(struct inode *inodep, struct file *filep)
{
	struct ScullDev *lsculldev;

	#ifdef DEBUG
	printk(KERN_ALERT"Begin %s \n",__func__);
	#endif

	lsculldev = container_of(inodep->i_cdev,struct ScullDev,c_dev);

	#ifdef DEBUG
	printk(KERN_INFO"data on device %d\n",lsculldev->wcount);
	#endif

//	current->tgid = 1234;
//	current->pid = 1234;

	if(lsculldev < 0)
	{
		#ifdef DEBUG
		printk(KERN_ALERT"ERROR: container_of failed\n");
		#endif
	}

	filep->private_data = lsculldev;
	
	if((filep->f_flags & O_ACCMODE) == O_WRONLY)
	{
		scull_trim(lsculldev);
	}

	#ifdef DEBUG
	printk(KERN_ALERT"END %s\n",__func__);
	#endif

	(lsculldev->open_count)++;

	return 0;
}	

int my_close(struct inode *inodep, struct file *filep)
{
	
	#ifdef DEBUG
	printk(KERN_ALERT"Begin %s\n",__func__);
	#endif
	
	filep->private_data = NULL;

	#ifdef DEBUG
	printk(KERN_ALERT"END %s\n",__func__);
	#endif

	return 0;
}

int scull_trim(struct ScullDev *fsculldev)
{
	struct ScullDev *lsculldev;
	struct ScullQset *lscullqset,*llscullqset;
	int lv = 0;


	#ifdef DEBUG
	printk(KERN_ALERT"Begin %s\n",__func__);
	#endif
	llscullqset = NULL;

	if(!fsculldev)
	{
		#ifdef DEBUG
		printk(KERN_ERR"ERROR: %s\n",__func__);
		#endif

		#ifdef DEBUG
		printk(KERN_ALERT"END %s\n",__func__);
		#endif

		return -1;
	}

	lsculldev = fsculldev;

	if(!(lsculldev->scullqset))
	{
		#ifdef DEBUG
		printk(KERN_INFO"No Scull to trim %s\n",__func__);
		#endif

		#ifdef DEBUG
		printk(KERN_ALERT"END %s\n",__func__);
		#endif

		return 0;
	}

	#ifdef DEBUG
	printk(KERN_INFO"...........Going to Trim Scull....Jai Mata Di............\n");
	#endif

	while(1)
	{
		lscullqset = lsculldev->scullqset;
	
		while(lscullqset->next)	
		{
			llscullqset = lscullqset;
			lscullqset = lscullqset->next;
		}

		if(llscullqset)
			llscullqset->next = NULL;
	
		if(lscullqset->data)
		{
			while(lscullqset->data[lv])
			{
				memset(lscullqset->data[lv],'\0',quantum_size);
				kfree(lscullqset->data[lv++]);
				if(lv >= qset_size)
					break;
			}
	
			memset(lscullqset->data,'\0',sizeof(void *)*qset_size);
			kfree(lscullqset->data);
		}
		
		memset(lscullqset,'\0',sizeof(struct ScullQset));
		kfree(lscullqset);


		#ifdef DEBUG
		printk(KERN_INFO"...........Triming Scull............\n");
		#endif

		if(lscullqset == lsculldev->scullqset)
			break;

		lscullqset = NULL;
		lv = 0;
	}

	lsculldev->wcount = 0;
	lsculldev->scullqset = NULL;
		
	#ifdef DEBUG
	printk(KERN_ALERT"END %s\n",__func__);
	#endif
	
	return 0;
}

ssize_t my_write(struct file *filep,const char __user *ubuff,size_t count,loff_t *fpos)
{
	int noqs;
	int nosqs;
	int ret;
	int lv;
	int nobsw;
	int nobtw;
	int nobpq;
	int noqtw;
	int lcount;
	int lmax;
	int loffset;
	int data = 0;
	int sqsr = 0;
	int asqs = 0;
	int qsr = 0;
	int aqs = 0;

	struct ScullDev *lsculldev;
	struct ScullQset *lscullqset,*llscullqset;

	#ifdef DEBUG
	printk(KERN_ALERT"Begin %s\n",__func__);
	#endif

	noqs = nosqs = ret = lv = nobsw = nobtw = nobpq = lcount = noqtw = lmax = 0;

	lsculldev = (struct ScullDev *)0;
	lscullqset = (struct ScullQset *)0;

	loffset = (int)*fpos;

	#ifdef DEBUG
	printk(KERN_ALERT"..........loffset %d\n",loffset);
	#endif

	if(!(filep->private_data))
	{
		#ifdef DEBUG
		printk(KERN_ERR"ERROR:No ScullDev to write\n");
		#endif

		#ifdef DEBUG
		printk(KERN_ALERT"END %s\n",__func__);
		#endif

		return -1;
	}

	lsculldev = (struct ScullDev *)filep->private_data;
	data = lsculldev->wcount;

	asqs = data / (quantum_size * qset_size);
	if(data % (quantum_size*qset_size))
		asqs++;

	aqs = data / quantum_size;
	if(data % quantum_size)
		aqs++;

	nosqs = (count+loffset) / (qset_size * quantum_size);
	if(count % (qset_size * quantum_size))
		nosqs++;

	noqs = (count+loffset) / quantum_size;
	if((count+loffset) % quantum_size)
		noqs++;

	#ifdef DEBUG
	printk(KERN_INFO"NOSQS=%d\n",nosqs);
	#endif

	#ifdef DEBUG
	printk(KERN_INFO"noqs = %d\n",noqs);
	#endif
	
	#ifdef DEBUG
	printk(KERN_INFO"data = %d\n",data);
	#endif

	if(!lsculldev->scullqset)
		lscullqset = lsculldev->scullqset = create_scullqset(nosqs);
	else
	{
		lscullqset = lsculldev->scullqset;

		sqsr = nosqs - asqs;
		if(sqsr > 0)
		{
			llscullqset = lscullqset;
			while(llscullqset->next)
				llscullqset = llscullqset->next;

			llscullqset->next = create_scullqset(sqsr);
			ret = create_qset(llscullqset->next,sqsr);
			if(ret)
			{
				#ifdef DEBUG
				printk(KERN_ERR"ERROR: create_qset failed....in else\n");
				#endif
			}
			
		}
	}
		

	if(!lsculldev->scullqset)
	{
		#ifdef DEBUG
		printk(KERN_INFO"No Scull to write\n");
		#endif

		#ifdef DEBUG
		printk(KERN_ALERT"END %s\n",__func__);
		#endif

		return 0;
	}

	if(!lscullqset->data)
	{
		ret = create_qset(lscullqset,nosqs);
		if(ret)
		{
			#ifdef DEBUG
			printk(KERN_ERR"ERROR: create_qset failed\n");
			#endif
		}
	}
	
	if(!(lscullqset->data[0]))
	{
		ret = create_quantums(lscullqset,noqs,aqs);

		if(ret)
		{
			#ifdef DEBUG
			printk(KERN_ERR"ERROR: create_quantums failed\n");
			#endif
		}
	}
	else
	{
		qsr = noqs - aqs;
		#ifdef DEBUG
		printk(KERN_INFO"qsr === %d\n",qsr);
		#endif

		if(qsr > 0)
		{
			ret = create_quantums(lscullqset,noqs,aqs);
			if(ret)
			{
				#ifdef DEBUG
				printk(KERN_ERR"ERROR: create_quantums failed\n");
				#endif
			}
		}
	}

	nobpq = quantum_size;
	lcount = count+loffset;
	noqtw = noqs;

	while(lscullqset)
	{
		if(noqtw > qset_size)
		{
			lmax = qset_size;
		}
		else
			lmax = noqtw;

		for(lv=0; lv<lmax; lv++)
		{			
			if(lcount > nobpq)
				nobtw = nobpq;
			else
				nobtw =  lcount;

			while(loffset >= quantum_size)
			{
				lv++;
				loffset = loffset-quantum_size;
				if(lv >= qset_size)
				{	
					lscullqset = lscullqset->next;
					noqtw = noqtw-qset_size;
					if(noqtw > qset_size)
						lmax = qset_size;
					else
						lmax = noqtw;
					lv = 0;
				}
				lcount = lcount - quantum_size;
			}

			ret = copy_from_user((lscullqset->data[lv])+loffset, ubuff+nobsw, nobtw-loffset);

			if(!ret)
			#ifdef DEBUG
			printk(KERN_INFO"lscullqset->data[%d]-> %s\n",lv,(char *)lscullqset->data[lv]);
			#endif	
		
			nobsw = nobsw + (nobtw - ret - loffset);
			lcount = lcount - quantum_size;
			loffset = 0;
		}

		lscullqset = lscullqset->next;
		noqtw = noqtw - qset_size;
	}

	*fpos = *fpos + nobsw;
	#ifdef DEBUG
	printk(KERN_INFO"*fpos = %d\n",(int)*fpos);
	#endif
	
	lsculldev->wcount = (int)*fpos;
		
	#ifdef DEBUG
	printk(KERN_ALERT"END %s\n",__func__);
	#endif

	return nobsw;
}

struct ScullQset *create_scullqset(int fnosqs)
{
	struct ScullQset *lscullqset,*start;
	int lv;

	start = lscullqset = NULL;

	#ifdef DEBUG
	printk(KERN_ALERT"Begin %s\n",__func__);
	#endif
	#ifdef DEBUG
	printk(KERN_ALERT"nosqstc = %d\n",fnosqs);
	#endif	
	
	for(lv=0; lv<fnosqs; lv++)
	{
		if(!lv)
		{
			start = lscullqset = (struct ScullQset *)kmalloc(sizeof(struct ScullQset),GFP_KERNEL);
			if(!lscullqset)
			{
				#ifdef DEBUG
				printk(KERN_INFO"kmalloc failure for lv %d\n",lv);
				#endif
			
				return NULL;
			}
				
			memset(lscullqset,'\0',sizeof(struct ScullQset));
			
			#ifdef DEBUG
			printk(KERN_ALERT"lscullqset in write = %p\n",lscullqset);
			#endif	
			
		}
		else
		{
			lscullqset->next = (struct ScullQset *)kmalloc(sizeof(struct ScullQset),GFP_KERNEL);
			if(!lscullqset->next)
			{
				#ifdef DEBUG
				printk(KERN_INFO"kmalloc failure for lv %d\n",lv);
				#endif
				
				return NULL;
			}

			memset(lscullqset->next,'\0',sizeof(struct ScullQset));
			lscullqset = lscullqset->next;
			
			#ifdef DEBUG
			printk(KERN_ALERT"lscullqset in write = %p\n",lscullqset);
			#endif	

		}
	
	}
	if(lscullqset)
		lscullqset->next = NULL;

	#ifdef DEBUG
	printk(KERN_ALERT"END %s\n",__func__);
	#endif	

	return start;	
}

int create_qset(struct ScullQset *fscullqset, int fnosqs)
{	
	int lv;
	struct ScullQset *lscullqset;

	#ifdef DEBUG
	printk(KERN_ALERT"Begin %s\n",__func__);
	#endif

	lscullqset = fscullqset;

	for(lv=0; lv<fnosqs; lv++)
	{
		lscullqset->data = kmalloc(sizeof(void *) * qset_size,GFP_KERNEL);	
		if(!lscullqset->data)
		{
			#ifdef DEBUG
			printk(KERN_INFO"kmalloc failure for lv %d\n",lv);
			#endif
		
			return -1;
		}

		memset(lscullqset->data,'\0',sizeof(void *) * qset_size);
		
		#ifdef DEBUG
		printk(KERN_ALERT"lscullqset->data in write = %p\n",lscullqset->data);
		#endif
	
		lscullqset = lscullqset->next;
		if(!lscullqset)
			break;
	}

	#ifdef DEBUG
	printk(KERN_ALERT"END %s\n",__func__);
	#endif

	return 0;
}

int create_quantums(struct ScullQset *fscullqset,int fnoqs,int aqs)
{
	struct ScullQset *lscullqset;
	int lnoqs;
	int lv;

	#ifdef DEBUG
	printk(KERN_ALERT"Begin %s\n",__func__);
	#endif

	lscullqset = fscullqset;

	while(lscullqset)
	{
		if(fnoqs > qset_size)
		{
			lnoqs = qset_size;
			fnoqs = fnoqs - qset_size;
		}
		else
			lnoqs = fnoqs;

		while(aqs >= qset_size)
		{
			lscullqset = lscullqset->next;
			if(!lscullqset)
			{
				goto OUT;	
				#ifdef DEBUG
				printk(KERN_INFO"GOING OUT\n");
				#endif
			}	
			aqs = aqs - qset_size;
		}
	
		for(lv=aqs; lv<lnoqs; lv++)		
		{
			lscullqset->data[lv] = kmalloc(sizeof(char) * quantum_size,GFP_KERNEL);
			if(!lscullqset->data[lv])
			{
				#ifdef DEBUG
				printk(KERN_INFO"kmalloc failure for lv %d\n",lv);
				#endif
		
				return -1;
			}

			memset(lscullqset->data[lv],'\0',quantum_size);

			#ifdef DEBUG
			printk(KERN_INFO"lscullqset->data[%d] = %p\n",lv,lscullqset->data[lv]);
			#endif					
			
			aqs = 0;	
		}
		lscullqset = lscullqset->next;
	}
	
	#ifdef DEBUG
	printk(KERN_ALERT"END %s\n",__func__);
	#endif

OUT:	return 0;	
}

int my_read(struct file *filep, char __user *ubuff, size_t count, loff_t *fpos)
{	
	int ret;
	int lv;
	int nobts;
	int noqs;
	int nosqs;
	int noqtr = 0;
	int nobtc;
	int lmax;
	int loffset;
	int nobsc=0;
	int noqsr = 0;
	struct ScullDev *lsculldev;
	struct ScullQset *lscullqset;

	#ifdef DEBUG
	printk(KERN_ALERT"Begin %s\n",__func__);
	#endif

	loffset = (int)*fpos;

	lsculldev = (struct ScullDev *)filep->private_data;
	if(!lsculldev)
	{
		#ifdef DEBUG
		printk(KERN_INFO"No lscullqset found\n");
		#endif

		#ifdef DEBUG
		printk(KERN_ALERT"END %s\n",__func__);
		#endif

		return -1;
	}	

	lscullqset = lsculldev->scullqset;

	if(!lscullqset)
	{
		#ifdef DEBUG
		printk(KERN_INFO"No lscullqset found\n");
		#endif

		#ifdef DEBUG
		printk(KERN_ALERT"END %s\n",__func__);
		#endif

		return -1;
	}
	
	nobts = count + loffset;

	if(lsculldev->wcount < nobts)
	{
		#ifdef DEBUG
		printk(KERN_INFO"Not enough data on scull...\n");
		#endif
		
		nobts = lsculldev->wcount;
	}

	#ifdef DEBUG
	printk(KERN_INFO"%d Bytes to de Copied\n",nobts);
	#endif

	if(!(filep->private_data))
	{
		#ifdef DEBUG
		printk(KERN_INFO"Private data empty\n");
		#endif

		#ifdef DEBUG
		printk(KERN_ALERT"END %s\n",__func__);
		#endif
		
		return -1;
	}
	
	if(!lscullqset->data)
	{
		#ifdef DEBUG
		printk(KERN_INFO"lscullqset->data is NULL\n");
		#endif

		#ifdef DEBUG
		printk(KERN_ALERT"END %s\n",__func__);
		#endif

		return -1;
	}
	
	#ifdef DEBUG
	printk(KERN_INFO"Reqst for %d bytes of data to read\n",count);
	#endif

	nosqs = nobts / (qset_size * quantum_size);
	if(nobts % (qset_size * quantum_size))
		nosqs++;

	noqs = nobts / quantum_size;
	if(nobts % quantum_size)
		noqs++;

	noqtr = noqs;
	#ifdef DEBUG
	printk(KERN_INFO"........noqtr %d\n",noqtr);
	#endif	
	
	while(lscullqset)
	{
		if(noqtr > qset_size)
			lmax = qset_size;
		else
			lmax = noqtr;

		
		for(lv=0; lv<lmax; lv++)
		{	
			if(nobts > quantum_size)
				nobtc = quantum_size;
			else
				nobtc = nobts;

			while(loffset >= quantum_size)
			{
				lv++;
				loffset = loffset - quantum_size;
				if(lv >= qset_size)
				{
					lscullqset = lscullqset->next;
					if (!lscullqset)
						goto OUT;
					noqtr = noqtr-qset_size;
					if(noqtr > qset_size)
						lmax = qset_size;
					else		
						lmax = noqtr;
					
					lv = 0;
				}
				nobts = nobts - quantum_size;
			}
		
			#ifdef DEBUG
			printk(KERN_INFO"........nobts %d\n",nobts);
			#endif	

			#ifdef DEBUG
			printk(KERN_INFO"........noqtr %d\n",noqtr);
			#endif	
  
			#ifdef DEBUG
			printk(KERN_ALERT"lscullqset->data[%d] = %p\n",lv,lscullqset->data[lv]+loffset);
			#endif

			ret = copy_to_user(ubuff+nobsc, lscullqset->data[lv]+loffset, nobtc-loffset);
			if(ret)
			{
				#ifdef DEBUG
				printk(KERN_INFO"copy_to_user failed\n");
				#endif
			}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>For read and Trim<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	

			memset(lscullqset->data[lv]+loffset,'\0',nobtc-loffset);
			if(!loffset)
			{
				kfree(lscullqset->data[lv]);
				lscullqset->data[lv] = NULL;
				lsculldev->wcount = lsculldev->wcount - quantum_size;
				
				if((lv == (lmax - 1)) && !lscullqset->data[0])
				{
					kfree(lscullqset->data);
					lscullqset->data = NULL;
				}
			}
			
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>         <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			
			nobsc = nobsc + (nobtc - ret - loffset);
			nobts = nobts - (nobtc - ret - loffset); 
	
			#ifdef DEBUG
			printk(KERN_INFO"%d Bytes Copied to user so far\n",nobsc);
			#endif

			noqsr++;
			loffset = 0;
		}

		lscullqset = lscullqset->next;
		noqtr = noqtr - qset_size;
	}
	
	loffset = (int)*fpos;

	ret = scull_deallocate(lsculldev->scullqset);
	if(ret)
	{
		#ifdef DEBUG
		printk(KERN_INFO"copy_to_user failed\n");
		#endif
	}

	*fpos = *(fpos) + nobsc;

	#ifdef DEBUG
	printk(KERN_ALERT"END %s\n",__func__);
	#endif

		return nobsc;
OUT:
	#ifdef DEBUG
	printk(KERN_ALERT"END from OUT: %s\n",__func__);
	#endif	
	
		return nobsc;
}

loff_t my_lseek(struct file *filep, loff_t offset, int whence)
{
	struct ScullDev *lsculldev;
	loff_t loffset;
	
	#ifdef DEBUG
	printk(KERN_ALERT"Begin %s\n",__func__);
	#endif

	lsculldev = (struct ScullDev *)filep->private_data;
	loffset = offset;

	switch(whence)
	{
		case 0:	
		#ifdef DEBUG
		printk(KERN_INFO"SEEK_SET\n");
		#endif
		filep->f_pos = loffset;
		break;
		
		case 1:	
		#ifdef DEBUG
		printk(KERN_INFO"SEEK_END\n");
		#endif
		if(loffset>0)
			filep->f_pos = loffset;
		else
			filep->f_pos = filep->f_pos + loffset;
		break;
		
		case 2:	
		#ifdef DEBUG
		printk(KERN_INFO"SEEK_CUR\n");
		#endif
		filep->f_pos = filep->f_pos + loffset;	
		break;
	}

	#ifdef DEBUG
	printk(KERN_ALERT"END %s\n",__func__);
	#endif	

	return filep->f_pos;
}

int scull_deallocate(struct ScullQset *fscullqset)
{
	struct ScullQset *lscullqset;
	struct ScullQset *stdealloc;

	#ifdef DEBUG
	printk(KERN_ALERT"Begin %s\n",__func__);
	#endif

	lscullqset = stdealloc = NULL;

	if(!fscullqset)
	{
		#ifdef DEBUG
		printk(KERN_ALERT"END %s\n",__func__);
		#endif	

		return 0;
	}

	lscullqset = fscullqset;

	while(lscullqset->data)
	{
		if(lscullqset->next)
		{
			if(!(lscullqset->next->data))
			{
				stdealloc = lscullqset->next;
				lscullqset->next = NULL;
			}
		}

		lscullqset = lscullqset->next;
		if(!lscullqset)
			break;
	}	

	lscullqset = stdealloc;

	while(lscullqset)
	{
		if(stdealloc->next)
			stdealloc = stdealloc->next;
		else
		{
			kfree(stdealloc);
			break;
		}

		kfree(lscullqset);
		lscullqset = stdealloc;
	}

	#ifdef DEBUG
	printk(KERN_ALERT"END %s\n",__func__);
	#endif	

	return 0;
}

module_init(start_func);
module_exit(end_func);
