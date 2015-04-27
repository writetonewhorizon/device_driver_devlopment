INSTALLDIR= $(shell pwd)/modules
ifneq ($(KERNELRELEASE),)
	obj-m := usb_pl2303.o
usb_pl2303_mod-objs := usb_pl2303.o

else
	KERNDIR ?= /lib/modules/$(shell uname -r)/build
#	KERNDIR ?= /home/porting/Olinuxino/linux-sunxi/out/lib/modules/3.4.29+/build
	PWD := $(shell pwd)
	
default:
	$(MAKE) -C $(KERNDIR) M=$(PWD) modules
	@rm -rf $(INSTALLDIR)
	@mkdir $(INSTALLDIR)
	@mv *.ko *.mod.c *.o .*.cmd $(INSTALLDIR)

clean:
	rm -rf $(INSTALLDIR)
	rm -rf my_node
	rm -rf open

endif

