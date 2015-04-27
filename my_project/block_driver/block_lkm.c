#include"header.h"
static void sbd_transfer(struct sbd_device *dev, sector_t sector,unsigned long nsect,char *buffer,int write)
{
	unsigned long offset=sector *logical_block_size;
	unsigned long nbytes= nsect*logical_block_Size;
		if((offset+nbytes)>dev_size)
		{
			printk(KERN_NOTICE"sbd :Beyond -end write(%ld %ld)\n",offset,nbytes);
		return;
		}
		if(write)
			memcpy(dev->data+offset,buffer,nbytes);
		else
			memcpy(buffer,dev->data+offset,buffer,nbytes);
}
				
	

static void sbull_request(struct request_queue *q)
{
	struct request *req;
	req=blk_fetch_request(q);
	while(req!=NULL)
	{
		if(req==NULL || (req->cmd_type != REQ_TYPE_FS))
		{
			printk(KERN_NOTICE"Skip non-CMD request\n");
			__blk_end_request_all(req,-EIO);
			continue;
			req=blk_fetch_request(q);
		}
		sbd_transfer(&Device,blk_rq_pos()	

}

int sbull_open(struct block_device *blk_device,fmode_t fmod)
{
	#ifdef DEBUG
		printk(KERN_INFO"Start :%s \n",__func__);
	#endif
	#ifdef DEBUG
		printk(KERN_INFO"End :%s \n",__func__);
	#endif
return 0;
}

int sbull_release(struct gendisk *gendisk,fmode_t fmod)
{
	#ifdef DEBUG
		printk(KERN_INFO"Start :%s \n",__func__);
	#endif
	#ifdef DEBUG
		printk(KERN_INFO"End :%s \n",__func__);
	#endif
return 0;
}
static void sbull_request(struct request_queue *q)
{
	#ifdef DEBUG
		printk(KERN_INFO"Start :%s \n",__func__);
	#endif
	#ifdef DEBUG
		printk(KERN_INFO"End :%s \n",__func__);
	#endif

}

int function_add(struct sbull_dev *fsbulldev)
{
	char name[]="blockdisk";
	sector_t size;
	#ifdef DEBUG
		printk(KERN_INFO"Start :%s \n",__func__);
	#endif
	size=512;
		#ifdef DEBUG
			printk(KERN_INFO"Start allocation disk");
		#endif	
	fsbulldev->gendisk=alloc_disk(1);
		#ifdef DEBUG
			printk(KERN_INFO"end allocation disk");
		#endif
	if(fsbulldev->gendisk)
	{
		#ifdef DEBUG
			printk(KERN_INFO"Allocation successfull");
		#endif
	}
	else
	{
		#ifdef DEBUG
			printk(KERN_INFO"Allocation unsuccessfull");
		#endif
	}
	fsbulldev->data=vmalloc(fsbulldev->size);
	if(fsbulldev->data==NULL)
	{
		printk(KERN_NOTICE"VMALLOC FAILURE.\n");
	}
	spin_lock_init(&fsbulldev->lock);
	fsbulldev->queue=blk_init_queue(sbull_request,&fsbulldev->lock);
	if(fsbulldev->queue)
	{
		printk(KERN_NOTICE"QUEUE INIT SUCCESS.\n");
	}
	else
	{
		printk(KERN_NOTICE"QUEUE INIT FAILS.\n");
	}
	
	fsbulldev->gendisk->major=major_number;
	fsbulldev->gendisk->first_minor=0;
	fsbulldev->gendisk->minors=1;
	sprintf(fsbulldev->gendisk->disk_name,"%s",name);
	fsbulldev->gendisk->fops=&fops;
	fsbulldev->gendisk->queue=fsbulldev->queue;
	fsbulldev->gendisk->flags=GENHD_FL_CD;
	fsbulldev->gendisk->private_data=fsbulldev;
	set_capacity(fsbulldev->gendisk,size);
		#ifdef DEBUG
			printk(KERN_INFO"start add disk");
		#endif
	add_disk(fsbulldev->gendisk);
		#ifdef DEBUG
			printk(KERN_INFO"end add disk");
		#endif
	#ifdef DEBUG
		printk(KERN_INFO"End :%s \n",__func__);
	#endif
return 0;
}


int __init initialize_function(void)
{
	int retval_register;
	int retval;
	#ifdef DEBUG
		printk(KERN_INFO"Start :%s \n",__func__);
	#endif
	retval_register=retval=0;
/*Register block driver*/
	retval_register=register_blkdev(major_number,DEVICE_NAME);
			printk(KERN_ERR"Retval_register value:%d\n",retval_register);
	if(retval_register<0)
	{
		#ifdef DEBUG
			printk(KERN_ERR"Registration failed");
		#endif
	}
	major_number=retval_register;
		#ifdef DEBUG
			printk(KERN_ERR"Major number:%d\n",major_number);
			printk(KERN_ERR"Minor number:%d\n",minor_number);
		#endif

	sbulldev=kmalloc(sizeof(struct sbull_dev ),GFP_KERNEL);
	if(sbulldev)
	{
			#ifdef DEBUG
				printk(KERN_ERR"Memory allocated");
			#endif
	}
	else
	{
			#ifdef DEBUG
				printk(KERN_ERR"Memory not allcated");
			#endif
	}
			#ifdef DEBUG
				printk(KERN_ERR"Memset start");
			#endif
	memset(sbulldev,'\0',sizeof(struct sbull_dev));
			#ifdef DEBUG
				printk(KERN_ERR"Memset end");
			#endif
		retval=function_add(sbulldev);
		if(retval<0)
		{
			#ifdef DEBUG
				printk(KERN_ERR"Registration failed");
			#endif
		}
			

	#ifdef DEBUG
		printk(KERN_INFO"End :%s \n",__func__);
	#endif
return 0;
}
void __exit cleanup_function(void)
{
//	int retval_unregister;
	#ifdef DEBUG
		printk(KERN_INFO"Start :%s \n",__func__);
	#endif
	
	del_gendisk(sbulldev->gendisk);
	
	unregister_blkdev(major_number,DEVICE_NAME);
	#ifdef DEBUG
		printk(KERN_INFO"End :%s \n",__func__);
	#endif

}
module_init(initialize_function);
module_exit(cleanup_function);
