#include"header1.h"
#include"usb_header.h"

struct priv_data{
	spinlock_t lock;
	u8 line_status;
	u8 line_control;
}*priv;

static int __init my_usb_init(void)
{
	#ifdef DEBUG
	printk(KERN_INFO"Start %s\n",__func__);	
	#endif
	
	usb_register(&my_usb_driver);
	
	#ifdef DEBUG
	printk(KERN_INFO"End %s\n",__func__);	
	#endif

	return 0;
}

static void __exit my_usb_exit(void)
{
	#ifdef DEBUG
	printk(KERN_INFO"Start %s\n",__func__);	
	#endif

	usb_deregister(&my_usb_driver);

	#ifdef DEBUG
	printk(KERN_INFO"End %s\n",__func__);	
	#endif
}

int my_probe (struct usb_interface *intf,const struct usb_device_id *id)
{
	#ifdef DEBUG
	printk(KERN_INFO"Start %s**********\n",__func__);	
	#endif

	if(!register_usb_ch_device())
		#ifdef DEBUG
		printk(KERN_INFO"Node created --------------->>> for Minor %d\n",lv++);	
		#endif
	
	intf->minor = minorno;

	sculldev->interface = intf;

 	my_dev_info(intf);

	#ifdef DEBUG
	printk(KERN_INFO"intf->usb_dev %p\n",intf->usb_dev);	
	#endif

	my_class = class_create(THIS_MODULE,"vikram");
	intf->usb_dev = device_create(my_class,NULL,sculldev->c_dev.dev,NULL,"my_node");
	
	#ifdef DEBUG
	printk(KERN_INFO"intf->usb_dev %p\n",intf->usb_dev);	
	#endif

	#ifdef DEBUG
	printk(KERN_INFO"intf->dev %p\n",&intf->dev);	
	#endif

	#ifdef DEBUG
	printk(KERN_INFO"intf->dev->parent %p\n",intf->dev.parent);	
	#endif

	#ifdef DEBUG
	printk(KERN_INFO"End %s\n",__func__);	
	#endif

	return 0;
}

void my_disconnect (struct usb_interface *intf)
{
	struct urb *my_urb;
	#ifdef DEBUG
	printk(KERN_INFO"Start %s\n",__func__);	
	#endif

	my_urb = container_of((interface_to_usbdev(intf)),struct urb,dev);

	usb_free_urb(my_urb);
	device_destroy(my_class,sculldev->c_dev.dev);
	class_destroy(my_class);

	cdev_del(&sculldev->c_dev);
        unregister_chrdev_region(sculldev->c_dev.dev,nod);
        #ifdef DEBUG
        printk(KERN_ALERT"%s unregisterd with major no %d\n",D_NAME,majorno);
        #endif
	
	#ifdef DEBUG
	printk(KERN_INFO"End %s\n",__func__);	
	#endif
}

int my_open(struct inode *inodep, struct file *filep)
{
	struct ScullDev *lsculldev;
	struct usb_device *lusb_dev;
	struct device *dev;
	struct usb_interface *lintf;
	struct urb *intr_urb;
	char *buff;
	int result,i;
	
	#ifdef DEBUG
	printk(KERN_INFO"Start %s\n",__func__);	
	#endif

	buff = "HELLO";

	lsculldev = container_of(inodep->i_cdev,struct ScullDev,c_dev);

        #ifdef DEBUG
        printk(KERN_INFO"data on device %d\n",lsculldev->wcount);
        #endif

        if(lsculldev < 0)
        {
                #ifdef DEBUG
                printk(KERN_ALERT"ERROR: container_of failed\n");
                #endif
        }

        filep->private_data = lsculldev;

        if((filep->f_flags & O_ACCMODE) == O_WRONLY)
        {
//	         scull_trim(lsculldev);
        }

	lintf = lsculldev->interface;
	lusb_dev = lsculldev->usb_dev = interface_to_usbdev(lintf);
	dev = lintf->usb_dev;
	if(!dev){
        	#ifdef DEBUG
     		printk(KERN_INFO"No dev in intf \n");
        	#endif
	}

	pl2303_vendor_write(8, 0, lusb_dev);
        pl2303_vendor_write(9, 0, lusb_dev);

	set_baud_rate(lintf);

	intr_urb = init_urb(lsculldev);
	
        pl2303_vendor_write(0, 0, lusb_dev);
        
	result = usb_submit_urb(intr_urb,GFP_KERNEL);

	if (result){
                printk(KERN_ERR"error %d failed submitting interrupt urb",result);
                return result;
        }

        pl2303_vendor_write(0, 0, lusb_dev);

	priv = (struct priv_data *)dev_get_drvdata(dev);

	printk(KERN_INFO"get_dev_drvdata successful with priv %p\n",priv);
	
//      printk(KERN_INFO"Line_status %x",priv->line_status);
//	printk(KERN_INFO"control %x",priv->line_control);

	result = usb_bulk_msg(lusb_dev,usb_sndbulkpipe(lusb_dev,0x02),(void*)buff,5,&i,100);
	
        printk(KERN_INFO"Result is %d i is %d",result,i);
            //    return result;

        #ifdef DEBUG
        printk(KERN_ALERT"END %s\n",__func__);
        #endif

        (lsculldev->open_count)++;

        return 0;
}

int my_close(struct inode *inodep,struct file *filep)	
{
	#ifdef DEBUG
	printk(KERN_INFO"Start %s\n",__func__);	
	#endif

	#ifdef DEBUG
	printk(KERN_INFO"End %s\n",__func__);	
	#endif
	
	return 0;
}

int register_usb_ch_device(void)
{
	int ret;

	#ifdef DEBUG
	printk(KERN_INFO"Start %s\n",__func__);	
	#endif

	if(!majorno){
		ret = alloc_chrdev_region(&dev,minorno,nod,D_NAME);
		if(ret){
			#ifdef DEBUG
			printk(KERN_ALERT"Registration Failed for dev_id %d\n",dev);
			#endif
			return -1;
		}

		#ifdef DEBUG
		printk(KERN_ALERT"%s registerd with Major dev_id %d\n",D_NAME, majorno = MAJOR(dev));
		#endif
	}	

	else{
		dev = MKDEV(majorno,++minorno);
		ret = register_chrdev_region(dev,nod,D_NAME);
		if(ret<0)
			printk(KERN_ALERT"Registration Failed for dev_id %d\n",dev);

		return -1;
      	}

	set_sculldev();
	init_sculldev();

	#ifdef DEBUG
	printk(KERN_INFO"End %s\n",__func__);	
	#endif	
	
	return 0;
}	

void set_sculldev(void)
{
        #ifdef DEBUG
        printk(KERN_ALERT"Begin %s\n",__func__);
        #endif

        sculldev = kmalloc(sizeof(struct ScullDev), GFP_KERNEL);
        memset(sculldev,'\0',sizeof(struct ScullDev));

	dev = MKDEV(majorno,lv);
	cdev_init(&sculldev->c_dev,&f_op);
	sculldev->c_dev.owner = THIS_MODULE;
	sculldev->c_dev.ops = &f_op;
	sculldev->c_dev.dev = dev;
	sculldev->c_dev.count = nod;
	cdev_add(&sculldev->c_dev,dev,nod);
        
        #ifdef DEBUG
        printk(KERN_ALERT"END %s\n",__func__);
        #endif
}

void init_sculldev(void)
{
        #ifdef DEBUG
        printk(KERN_ALERT"Begin %s\n",__func__);
        #endif
 
 	sculldev->quantum_size = QUANTUM_SIZE;
	sculldev->qset_size = QSET_SIZE;
	sculldev->device_size = DEVICE_SIZE;
	sculldev->data_size = DATA_SIZE;
	sculldev->open_count = OPEN_COUNT;

        #ifdef DEBUG
        printk(KERN_ALERT"END %s\n",__func__);
        #endif
}

void my_dev_info(struct usb_interface *intf)
{
	int i;
	int noep;
	struct usb_device *dev;

        #ifdef DEBUG
        printk(KERN_ALERT"Begin %s\n",__func__);
        #endif

        #ifdef DEBUG
        printk(KERN_INFO"Device have %d Alt Settings and Minor No is %d\n",intf->num_altsetting,intf->minor);
        #endif

        #ifdef DEBUG
        printk(KERN_INFO"Device NO of end point %d\n",noep = (int)intf->cur_altsetting->desc.bNumEndpoints);
        #endif

        for(i=0; i<noep; ++i)
                sculldev->my_end_desc[i] = (intf->cur_altsetting->endpoint[i].desc);

        if((sculldev->my_end_desc[0].bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_INT){
                #ifdef DEBUG
                printk(KERN_INFO"DEVICE HAVE INT ENDPOINT With address %x\n",intf->cur_altsetting->endpoint->desc.bEndpointAddress);   
                #endif
        }

        if((sculldev->my_end_desc[1].bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_BULK){
                #ifdef DEBUG
                printk(KERN_INFO"DEVICE HAVE BULK_1 ENDPOINT With address %x\n",intf->cur_altsetting->endpoint[1].desc.bEndpointAddress);
                #endif
        }

        if((sculldev->my_end_desc[2].bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_BULK){
                #ifdef DEBUG
                printk(KERN_INFO"DEVICE HAVE BULK_2 ENDPOINT With address %x\n",intf->cur_altsetting->endpoint[2].desc.bEndpointAddress);
                #endif
        }

	dev = interface_to_usbdev(intf);

	if (dev->descriptor.bMaxPacketSize0 == 0x40){
        	#ifdef DEBUG
        	printk(KERN_INFO"Device is HX Type\n");
        	#endif
	}

        #ifdef DEBUG
        printk(KERN_ALERT"END %s\n",__func__);
        #endif
}
	
int my_write(struct file *filep, const char __user *ubuff, size_t count, loff_t *fpos)
{
	int noqs;
        int nosqs;
        int ret;
        int lv;
       // int i;
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

        if(!(filep->private_data)){
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
        else{
                lscullqset = lsculldev->scullqset;

                sqsr = nosqs - asqs;
                if(sqsr > 0){
                        llscullqset = lscullqset;
                        while(llscullqset->next)
                                llscullqset = llscullqset->next;

                        llscullqset->next = create_scullqset(sqsr);
                        ret = create_qset(llscullqset->next,sqsr);
                        if(ret){
                                #ifdef DEBUG
                                printk(KERN_ERR"ERROR: create_qset failed....in else\n");
                                #endif
                        }
                }
        }


        if(!lsculldev->scullqset){
                #ifdef DEBUG
                printk(KERN_INFO"No Scull to write\n");
                #endif

                #ifdef DEBUG
                printk(KERN_ALERT"END %s\n",__func__);
                #endif

                return 0;
        }

        if(!lscullqset->data){
                ret = create_qset(lscullqset,nosqs);
                if(ret){
                        #ifdef DEBUG
                        printk(KERN_ERR"ERROR: create_qset failed\n");
                        #endif
                }
        }

        if(!(lscullqset->data[0])){
                ret = create_quantums(lscullqset,noqs,aqs);

                if(ret){
                        #ifdef DEBUG
                        printk(KERN_ERR"ERROR: create_quantums failed\n");
                        #endif
                }
        }
        else{
                qsr = noqs - aqs;
                #ifdef DEBUG
                printk(KERN_INFO"qsr === %d\n",qsr);
                #endif

                if(qsr > 0){
                        ret = create_quantums(lscullqset,noqs,aqs);
                        if(ret){
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
                if(noqtw > qset_size){
                        lmax = qset_size;
                }
                else
                        lmax = noqtw;

                for(lv=0; lv<lmax; lv++){
                        if(lcount > nobpq)
                                nobtw = nobpq;
                        else
                                nobtw =  lcount;

                        while(loffset >= quantum_size){
                                lv++;
                                loffset = loffset-quantum_size;
                                if(lv >= qset_size){
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
        printk(KERN_ALERT"END %s\n",__func__);
        #endif
	
	return nobsc;
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

        for(lv=0; lv<fnosqs; lv++){
                if(!lv){
                        start = lscullqset = (struct ScullQset *)kmalloc(sizeof(struct ScullQset),GFP_KERNEL);
                        if(!lscullqset){
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
                else{
                        lscullqset->next = (struct ScullQset *)kmalloc(sizeof(struct ScullQset),GFP_KERNEL);
                        if(!lscullqset->next){
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

        for(lv=0; lv<fnosqs; lv++){
                lscullqset->data = kmalloc(sizeof(void *) * qset_size,GFP_KERNEL);
                if(!lscullqset->data){
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

        while(lscullqset){
                if(fnoqs > qset_size){
                        lnoqs = qset_size;
                        fnoqs = fnoqs - qset_size;
                }
                else
                        lnoqs = fnoqs;

                while(aqs >= qset_size){
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

                for(lv=aqs; lv<lnoqs; lv++){
                        lscullqset->data[lv] = kmalloc(sizeof(char) * quantum_size,GFP_KERNEL);
                        if(!lscullqset->data[lv]){
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

OUT:    return 0;
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

int set_baud_rate(struct usb_interface *intf)
{
	int i;
	struct usb_device *my_dev;
	int baud = 19200;
	char *buf;

        #ifdef DEBUG
        printk(KERN_ALERT"Begin %s\n",__func__);
        #endif

	my_dev = interface_to_usbdev(intf);
	
	buf = kmalloc(7,GFP_KERNEL);
        if(!buf){
       		#ifdef DEBUG
                printk(KERN_INFO"kmalloc failure for lv %d\n",lv);
                #endif

		return -1;
        }
	memset(buf,'\0',7);

//Reading Baud
	i = usb_control_msg(my_dev,usb_rcvctrlpipe(my_dev, 0),GET_LINE_REQUEST, GET_LINE_REQUEST_TYPE,0, 0, buf, 7, 100);
	#ifdef DEBUG
	printk(KERN_INFO"Baud Rate is %d\n",*(int *)buf);
	#endif

	memset(buf,'\0',7);

// Setting baud rate in First (LSB) four bytes of buf
	buf[0] = baud & 0xff;
	buf[1] = (baud >> 8) & 0xff;
	buf[2] = (baud >> 16) & 0xff;
	buf[3] = (baud >> 24) & 0xff;

// Setting Parity and No. of Stop bits
	buf[4] = 0x00;
	buf[5] = 0x00;
	
	buf[6] = 0x08; //Character Size
	
	i = usb_control_msg(my_dev,usb_sndctrlpipe(my_dev, 0),SET_LINE_REQUEST, SET_LINE_REQUEST_TYPE,0, 0, buf, 7, 100);

//Reading Baud
	i = usb_control_msg(my_dev,usb_rcvctrlpipe(my_dev, 0),GET_LINE_REQUEST, GET_LINE_REQUEST_TYPE,0, 0, buf, 7, 100);

	#ifdef DEBUG
	printk(KERN_INFO"Baud Rate is %d\n",*(int *)buf);
	#endif

//	memset(buf,'\0',7);

        #ifdef DEBUG
        printk(KERN_ALERT"END %s\n",__func__);
        #endif

	return 0;
}

int pl2303_vendor_write(__u16 value, __u16 index,struct usb_device *dev)
{
	int res;
        #ifdef DEBUG
        printk(KERN_ALERT"Begin %s\n",__func__);
        #endif

        res = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),VENDOR_WRITE_REQUEST, VENDOR_WRITE_REQUEST_TYPE,
                        value, index, NULL, 0, 100);
	
        #ifdef DEBUG
        printk(KERN_ALERT"END %s\n",__func__);
        #endif

        return res;
}

struct urb * init_urb(struct ScullDev *fsculldev)
{
	struct urb *l_urb;
	struct usb_device *dev;
	char *buff;
	void *context = kmalloc(1,GFP_KERNEL);

	memset(context,0,1);

        #ifdef DEBUG
        printk(KERN_ALERT"Begin %s\n",__func__);
        #endif

	buff = (char *)kmalloc(10,GFP_KERNEL);
	memset(buff,0,10);

	dev = fsculldev->usb_dev;
	
	l_urb = usb_alloc_urb(0,GFP_ATOMIC);

	usb_fill_int_urb(l_urb,dev,usb_rcvintpipe(dev,0x81),(void *)buff,10,my_complete,0,1);
	
        #ifdef DEBUG
        printk(KERN_ALERT"END %s\n",__func__);
        #endif

	return l_urb;
}

void my_complete(struct urb *cmp_urb)
{
	int i,result;

        #ifdef DEBUG
        printk(KERN_ALERT"Begin %s\n",__func__);
        #endif

	for(i=0;i<10;i++){
        	#ifdef DEBUG
        	printk(KERN_INFO"Buf in intr_urb BYTE %d is %x\n",i,*((char *)(cmp_urb->transfer_buffer+i)));
       	 	#endif
	}

	result = usb_submit_urb(cmp_urb,GFP_ATOMIC);
	if (result){
                printk(KERN_ERR"error %d failed submitting interrupt urb",result);
        }
        #ifdef DEBUG
        printk(KERN_ALERT"END %s\n",__func__);
        #endif
}

module_init(my_usb_init);
module_exit(my_usb_exit);
