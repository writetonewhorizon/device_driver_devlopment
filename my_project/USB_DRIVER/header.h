#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/slab.h>
#include<linux/fs.h>
#include<linux/sched.h>
#include<linux/uaccess.h>
#include<linux/moduleparam.h>
#include<linux/hardirq.h>
#include<linux/proc_fs.h>
 #include<linux/hid.h>
//#include<usr/src/kernels/linux-3.8.6/drivers/hid/usbhid.c>

#include<linux/usb/input.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("NEERAJ_MISHRA USB_DRIVER");
#ifndef NOD
#define NOD 4
#endif
 
#ifndef DEFINE
#define DEFINE
#endif
static int usb_kbd_init(void);
static void usb_kbd_exit(void);
static int usb_kbd_probe(struct usb_interface *,struct usb_device_id *);
//static int usb_kbd_alloc_mem(struct usb_device,struct usb_kbd);
//static void usb_kbd_free_mem(struct usb_device ,struct usb_kbd);


