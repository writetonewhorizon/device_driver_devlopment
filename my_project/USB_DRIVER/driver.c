#include"header.h"
struct usb_kbd {/*This is a Private Data Structure Which is being used by Driver Futher..*/
        struct input_dev *dev;
        struct usb_device *usbdev;
        unsigned char old[8];
        struct urb *irq, *led;
        unsigned char newleds;
        char name[128];
        char phys[64];

        unsigned char *new;
        struct usb_ctrlrequest *cr;
        unsigned char *leds;
        dma_addr_t new_dma;
        dma_addr_t leds_dma;

        spinlock_t leds_lock;
        bool led_urb_submitted;

};
static struct usb_device_id usb_id_table[]= {
	{USB_DEVICE(0x152d,0x2329)},	/*Here we are writing HID value, Vendor_id,Product_id*/
	{USB_DEVICE(0x0bc2,0x2312)},
	{USB_DEVICE(0x03f0,0xe507)},
	{USB_DEVICE(0x046d,0xc31d)},
	{}/*Terminating entry*/
};
MODULE_DEVICE_TABLE(usb,usb_id_table);/*This is used to access the user level tools and tell what device does our driver will control, for usb 1st argv. is usb..*/
static struct usb_driver usb_kbd_driver= {
	//.owner=THIS_MODULE,
	.name= "KEYBOARD_USB",
	.probe= usb_kbd_probe,
	//.disconnect= usb_kdb_disconnect,
	.id_table= usb_id_table, /*Yaha par usb_device_id ka varible dete hai.... */
};
static int usb_kbd_init(void)
{
	int ret;
	#ifdef DEFINE
	printk(KERN_INFO "Start: %s\n",__func__);
	#endif  
	ret=usb_register(&usb_kbd_driver);/*Ye register hamne USB core ke sath kiya hai..*/
	if(ret == 0)
	{		
		#ifdef DEFINE
		printk(KERN_INFO "ret=%d",ret);
		printk(KERN_INFO "YOUR DEVICE GET REGISTER SUCCESSFULLY......\n");
		#endif
	}
	else
	{
		#ifdef DEFINE
		printk(KERN_INFO "ERROR IN REGISTRATION OF DEVICE.......\n");
		err("USB_REGISTER FAILS and ERROR NO. IS==>%d\n",ret);
		#endif
		goto OUT;
	}
	return 0;
OUT:
	return 1;
	#ifdef DEFINE
	printk(KERN_INFO "End: %s\n",__func__);
	#endif  
}
static int usb_kbd_alloc_mem(struct usb_device *dev,struct usb_kbd *kbd)
{
	kbd->irq=usb_alloc_urb(0,GFP_KERNEL);/*Here 1st argu. is 0,if we are using for only Isco. endpoint then we will use iso_packets to no. of             isoc. packets are to be send otherwise it will be 0*/
	#ifdef DEFINE
	printk(KERN_INFO "kbd->irq=%p\n",kbd->irq);
	#endif
	kbd->new=usb_alloc_coherent(dev,8,GFP_ATOMIC,&kbd->new_dma);
	#ifdef DEFINE
	printk(KERN_INFO "kbd->new=%p\n",kbd->new);
	#endif
	return 0;
}
static void usb_kbd_free_mem(struct usb_device *dev,struct usb_kbd *kbd)
{
	usb_free_urb(kbd->irq);/*Here 1st argu. is 0,if we are using for only Isco. endpoint then we will use iso_packets to no. of             isoc. packets are to be send otherwise it will be 0*/
	#ifdef DEFINE
	printk(KERN_INFO "For free kbd->irq=%p\n",kbd->irq);
	#endif
	usb_free_coherent(dev,8,kbd->new,kbd->new_dma);
	#ifdef DEFINE
	printk(KERN_INFO "For free kbd->new=%p\n",kbd->new);
	#endif
}
static int usb_kbd_probe(struct usb_interface *iface, struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(iface);/*Yaha par hamne kernel ko Device ke bare me bataya hai, usb_interface ka varible ka 
	address de kar kyoki usb_interface ke ander sare device ke bareme diya hota hai,giving starting address of usb_device which is in side the USB device and also giving the starting address of usb_interface pointer to (equal to)*iface pointer which we have been taken in our driver(usb_interface *iface)...*/
	int i,a,b,c,j,d,e;
	struct usb_host_interface *interface;
	struct usb_endpoint_descriptor *endpoint,*endpoint1,*endpoint2;
	struct usb_kbd *kbd; /*Our private structure*/
	struct input_dev *input_dev;/* Structure to interface with input subsystem */
	int pipe,maxp;
	int error=-ENOMEM;
	#ifdef DEFINE
	printk(KERN_INFO "Start: %s\n",__func__);
	#endif  
	interface=iface->cur_altsetting; /*Giving starting address of usb_host_interface *cul_alsetting varible,this means that currently active alsetting*/
//	if(interface->desc.bNumEndpoints!=1)
//	return -ENODEV;
	//endpoint=interface->endpoint;
	printk(KERN_INFO "<----------------NO. OF END POINTS IN INTERFACE---------------->");
	printk(KERN_INFO "No. of Endpoints=%d\n",interface->desc.bNumEndpoints);/*Here desc is varible of usb_interface_descripter in that bNumEndpoints is a   varible */
	for(i=0;i<4;i++)
	{
		printk(KERN_INFO "<----------------NO. OF END POINTS IN INTERFACE AND THEIR ADDRESSES---------------->");
		printk(KERN_INFO "%d\n",interface->endpoint[i].desc.bDescriptorType);
		printk(KERN_INFO "%d\n",interface->endpoint[i].desc.bmAttributes & 0x03);
		a=interface->endpoint[i].desc.bmAttributes & 0x03;/*We can find endpoint no. also by interface->endpoint[i].desc.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK==USB_ENDPOINT_XFER_INT which tell type of mask same as for bulk and Isoc.*/	
		switch(a)
		{
			case 0:
				printk(KERN_INFO "This is Control Endpoint\n");
				printk(KERN_INFO "Address of Control Endpoint==%u\n",interface->endpoint[a].desc.bEndpointAddress);
				b=interface->endpoint[a].desc.bEndpointAddress & USB_DIR_IN;
				if(b==1)
					printk(KERN_INFO "This is Input Endpoint\n");
				else
					printk(KERN_INFO "This is Not Input Endpoint\n");
				c=interface->endpoint[a].desc.bEndpointAddress & USB_DIR_OUT;
				if(c==0)
					printk(KERN_INFO "This is OUT Endpoint\n");
				else
					printk(KERN_INFO "This is Not OUT Endpoint\n");
				break;
			case 1:
				printk(KERN_INFO "This is Isocronous Endpoint\n");
				printk("Address of Isocronous Endpoint==%u\n",interface->endpoint[a].desc.bEndpointAddress);
				b=interface->endpoint[a].desc.bEndpointAddress & USB_DIR_IN;
				if(b==1)
					printk(KERN_INFO "This is Input Endpoint\n");
				else
					printk(KERN_INFO "This is Not Input Endpoint\n");
				c=interface->endpoint[a].desc.bEndpointAddress & USB_DIR_OUT;
				if(c==0)
					printk(KERN_INFO "This is OUT Endpoint\n");
				else
					printk(KERN_INFO "This is Not OUT Endpoint\n");
				break;
			case 2:
				printk("This is Bulk Endpoint\n");
				printk("Address of Bulk Endpoint==%u\n",interface->endpoint[a].desc.bEndpointAddress);
				b=interface->endpoint[a].desc.bEndpointAddress & USB_DIR_IN;
				if(b==1)
					printk(KERN_INFO "This is Input Endpoint\n");
				else
					printk(KERN_INFO "This is Not Input Endpoint\n");
				c=interface->endpoint[a].desc.bEndpointAddress & USB_DIR_OUT;
				if(c==0)
					printk(KERN_INFO "This is OUT Endpoint\n");
				else
					printk(KERN_INFO "This is Not OUT Endpoint\n");
				break;
			case 3:
				printk("This is Interrupt Endpoint\n");
				printk("Address of Interrupt Endpoint==%u\n",interface->endpoint[a].desc.bEndpointAddress);
				b=interface->endpoint[a].desc.bEndpointAddress & USB_DIR_IN;
				if(b==1)
					printk(KERN_INFO "This is Input Endpoint\n");
				else
					printk(KERN_INFO "This is Not Input Endpoint\n");
				c=interface->endpoint[a].desc.bEndpointAddress & USB_DIR_OUT;
				if(c==0)
					printk(KERN_INFO "This is OUT Endpoint\n");
				else
					printk(KERN_INFO "This is Not OUT Endpoint\n");
				break;
		}
	}
	//endpoint1=interface->endpoint;
	for(j=0;j<4;j++)
	{
		endpoint1=&interface->endpoint[j].desc;
		d=usb_endpoint_is_int_in(endpoint1);
		printk(KERN_INFO "d(IN)=%d\n",d);/*IN means that wheather we can take data from device */
		if(d==1)
		endpoint2=&interface->endpoint[j].desc;
		d=usb_endpoint_is_int_out(endpoint1);	
		printk(KERN_INFO "d(OUT)=%d\n",d);/*OUT means that wheather we give take data to the device */
		if(d==1)
		endpoint2=&interface->endpoint[j].desc;
	}
	//endpoint=&interface->endpoint[0].desc;/*Yaha par hamne pahale endpoint ka starting address de diya hai....*/
	//if(!usb_endpoint_is_int_in(endpoint))
	//return -ENODEV;
	pipe=usb_rcvintpipe(dev,endpoint2->bEndpointAddress);/*Yaha par ek pipe banaya hai jo Interrupt Endpoint se Attach hoga aur waha se data send         ya recieve karega par yaha par hanme receive pipe banaya hai,yaha par 1st argv. dev hai jo usb_device ka  pointer varible hai and 2nd is provi	    ding address of particular endpoint address,Yaha par hamlog urbs bhe use karsakte hai for large data transfer from/to endpoints but here we have been used pipe here bcoz this is interrupt endpoint which transfer small data(1 byte) so we have been used pipe here..*/
	#ifdef DEFINE
	printk(KERN_INFO "PIPE====>%d\n",pipe);
	#endif  
	maxp=usb_maxpacket(dev,pipe,usb_pipeout(pipe));/*Here we getting information about the max size packet of Endpoint can hold this function return the endpoint2->wMaxPacketSize,in this we are directly accessing the particular endpoint and then derefrencing the mMaxPacketSize,it also tells that how many no. of bytes this particular endpoint(interrupt,Bulk,Ischo.) can transfer data.*/
	#ifdef DEFINE
	printk(KERN_INFO "MAX SIZE OF ENDPOINT====>%d\n",maxp);
	#endif  
	kbd=kzalloc(sizeof(struct usb_kbd) , GFP_KERNEL); 
	#ifdef DEFINE
	printk(KERN_INFO "ADDRESS OF KBD====>%p\n",kbd);/*Here we are allocating size to usb_kdb structure(pointer varible *kbd) which is our private         structure,further we will use it,this structure is just a backup of information about usb device attached..*/
	#endif  
	input_dev=input_allocate_device();/*Here we are allocating size to structure which is our input system structure which will further give to 	      our input system to tell everything(information) about the usb device..*/
	#ifdef DEFINE
	printk(KERN_INFO "ADDRESS OF INPUT_DEV====>%p\n",input_dev);
	#endif  
	
	/*<================================= Here we are allocating URBs =========================================>*/
	e=usb_kbd_alloc_mem(dev,kbd);
	#ifdef DEFINE
	printk(KERN_INFO "Returned from usb_kbd_alloc_mem====>%d\n",e);
	#endif  
	kbd->usbdev=dev;/*Yaha par hamne usbdev jo structure usb_kbd ke andar usb_device (*usbdev) ka pointer hai usko usb device ke usb_device ka           starting address de rahe hai jisse ke vo hamare private structure ke andar save ho jaye for further refference*/
	kbd->dev=input_dev;/*Yaha par private structure ke andar input_dev *dev pointer ko input_dev(jo original hai) uska starting address de rahe           hai for further refference*/
	usb_kbd_free_mem(dev,kbd);
	return 0;
	#ifdef DEFINE
	printk(KERN_INFO "End: %s\n",__func__);
	#endif  
}
/*static void usb_kbd_disconnect(struct usb)
{

}*/
static int initialization_func(void)
{
	/*struct task_struct *my_parent = current->parent;
	struct task_struct *my_real_parent = current->real_parent;
	struct task_struct *task;
	struct list_head *list;*/
	#ifdef DEFINE
	printk(KERN_INFO "Start :%s\n",__func__);
	#endif
	#ifdef DEFINE
	//for_each_process(task)
//	{
		printk(KERN_INFO "Process is: %s Pid is: %d\n",current->comm,current->pid);
//	}
	#endif
	usb_kbd_init();
	//struct task_struct *my_parent = current->parent;
/*	#ifdef DEFINE
	printk(KERN_INFO "MY_PARENT pid: %d\n",*(int *)my_parent);
	printk(KERN_INFO "MY_REAL_PARENT pid: %d\n",*(int *)my_real_parent);
	printk(KERN_INFO "MY_CHILDREN pid1==>%d\n",current->children);
	#endif
	list_for_each(list,&current->children)
	{
		task=list_entry(list,struct task_struct,sibling);
		#ifdef DEFINE
		printk(KERN_INFO "MY_CHILDREN pid==>%d\n",*(int* )task);
		#endif
	}*/
	#ifdef DEFINE
	printk(KERN_INFO "End   :%s\n",__func__);
	#endif
	return 0;
}
static void usb_kbd_exit(void)
{
//	int a;
	#ifdef DEFINE
	printk(KERN_INFO "Start :%s\n",__func__);
	#endif
	usb_deregister(&usb_kbd_driver);/*Yaha par hamne de-register kiya hai USB core ke sath..*/
	#ifdef DEFINE
	printk(KERN_INFO "Device Get Deregistered Successfully...\n");
	#endif
	#ifdef DEFINE
	printk(KERN_INFO "End   :%s\n",__func__);
	#endif
}
static void exit_func(void)
{
	#ifdef DEFINE
	printk(KERN_INFO "Start :%s\n",__func__);
	#endif
	#ifdef DEFINE
	printk(KERN_INFO "Process is: %s Pid is: %d\n",current->comm,current->pid);
	#endif
	usb_kbd_exit();
	#ifdef DEFINE
	printk(KERN_INFO "End   :%s\n",__func__);
	#endif
}
module_init(initialization_func);
module_exit(exit_func);
