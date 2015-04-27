#include"header.h"

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

	#ifdef DEBUG
	printk(KERN_INFO"Device have %d Alt Settings\n",intf->num_altsetting);	
	#endif
	
	#ifdef DEBUG
	printk(KERN_INFO"Device NO of end point %d\n",(int)intf->cur_altsetting->desc.bNumEndpoints);	
	#endif

	if((intf->cur_altsetting->endpoint->desc.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_INT)
	{
		#ifdef DEBUG
		printk(KERN_INFO"DEVICE HAVE INT ENDPOINT With address %x\n",intf->cur_altsetting->endpoint->desc.bEndpointAddress);	
		#endif
	}

	if(((intf->cur_altsetting->endpoint + 1)->desc.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_BULK)
	{
		#ifdef DEBUG
		printk(KERN_INFO"DEVICE HAVE BULK_1 ENDPOINT With address %x\n",intf->cur_altsetting->endpoint[1].desc.bEndpointAddress);	
		#endif
	}

	if(((intf->cur_altsetting->endpoint + 2)->desc.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_BULK)
	{
		#ifdef DEBUG
		printk(KERN_INFO"DEVICE HAVE BULK_2 ENDPOINT With address %x\n",intf->cur_altsetting->endpoint[2].desc.bEndpointAddress);	
		#endif
	}

	#ifdef DEBUG
	printk(KERN_INFO"End %s\n",__func__);	
	#endif

	return 0;
}

void my_disconnect (struct usb_interface *intf)
{
	#ifdef DEBUG
	printk(KERN_INFO"Start %s\n",__func__);	
	#endif

	#ifdef DEBUG
	printk(KERN_INFO"End %s\n",__func__);	
	#endif
}

module_init(my_usb_init);
module_exit(my_usb_exit);
