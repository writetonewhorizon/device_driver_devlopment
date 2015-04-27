INSTALLDIR= $(shell pwd)/modules
ifneq ($(KERNELRELEASE),)
	obj-m := ch_d.o
ch_d_mod-objs := ch_d.o

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
	rm -rf my_nod
	rm -rf my_app

endif

