#define SET_LINE_REQUEST_TYPE           0x21
#define SET_LINE_REQUEST                0x20

#define SET_CONTROL_REQUEST_TYPE        0x21
#define SET_CONTROL_REQUEST             0x22

#define GET_LINE_REQUEST_TYPE           0xa1
#define GET_LINE_REQUEST                0x21

#define UART_STATE                      0x08
#define UART_STATE_TRANSIENT_MASK       0x74

#define VENDOR_WRITE_REQUEST_TYPE       0x40
#define VENDOR_WRITE_REQUEST            0x01

#define VENDOR_READ_REQUEST_TYPE        0xc0
#define VENDOR_READ_REQUEST             0x01

static struct class *my_class = NULL;
//static struct device *my_dev = NULL; 

int my_probe(struct usb_interface *,const struct usb_device_id *);
void my_disconnect(struct usb_interface *);

struct usb_device_id my_table[]={
	{USB_DEVICE(0x067b,0x2303)},
	{}
};

struct usb_driver my_usb_driver={
	.name = "my_usb",
	.probe=my_probe,
	.disconnect=my_disconnect,
	.id_table=my_table	
};

int register_usb_ch_device(void);
void my_dev_info(struct usb_interface *);
int set_baud_rate(struct usb_interface *);
int pl2303_vendor_write(__u16 value, __u16 index,struct usb_device *);
void my_complete(struct urb *);
struct urb * init_urb(struct ScullDev *);
