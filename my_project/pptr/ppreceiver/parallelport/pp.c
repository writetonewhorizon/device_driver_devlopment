#include"header.h"

irqreturn_t handler_irq(int,void *);
unsigned char ret_inbd;
//unsigned char ret_inbd;
void scull_init()
{
int ret_check;
struct resource *ret_request;
int first;
                scull_Dev->device_size=device_size;
                 scull_Dev->data_size=DATA_SIZE;
                 scull_Dev->quantum_size=QUANTUM_SIZE;
                 scull_Dev->qset_size=QSET_SIZE;
                printk(KERN_ALERT "Device_size:%d\n",scull_Dev->device_size);
                printk(KERN_ALERT "Data_size:%d\n",scull_Dev->data_size);
first = START;
ret_check=check_region(first,3);
  printk(KERN_ALERT"ret_check:%d\n",ret_check);
if(ret_check<0)
release_region(first,3);
//msleep(1000);

//release_region(first,3);
ret_request=request_region(first,3,"parallelport");
  printk(KERN_ALERT"ret_request:%d\n",(int)ret_request);

}


static int linuxworld_init(void)
{
int ret,ret_cdev,count;
  unsigned char ret_interrupt;
	      ret=alloc_chrdev_region(&dev,minorno,cm,DEVICE_NAME);
        if(ret<0)
        printk(KERN_ALERT "fail to register alloc_chrdev\n");
        printk(KERN_ALERT "LINUXWORLD Entry\n");
        printk(KERN_ALERT "registering mydriver\n");

        majorno=MAJOR(dev);
        minorno=MINOR(dev);
        printk(KERN_ALERT "majorno:%d minorno:%d \n",majorno,minorno);
	

	 scull_Dev=kmalloc((sizeof(struct scull_dev) * cm),GFP_KERNEL);
        memset(scull_Dev,'\0',sizeof(scull_Dev));
        
                cdev_init(&scull_Dev->cDev,&fops);
                scull_Dev->cDev.owner=THIS_MODULE;
                scull_Dev->cDev.ops=&fops;
                count=scull_Dev->cDev.count=cm;
                scull_Dev->scull_Qset=NULL;
                ret_cdev=cdev_add(&scull_Dev->cDev,dev, count);
                if(ret_cdev)
                        printk(KERN_NOTICE "Fail to add cdev to kernel\n");
                scull_Dev->cDev.dev=MKDEV(majorno,minorno);
                majorno=MAJOR(scull_Dev->cDev.dev);
                minorno=MINOR(scull_Dev->cDev.dev);
                printk(KERN_ALERT "majorno____:%d minorno____:%d \n",majorno,minorno);
        
        scull_init();
outb(16,0x037a);
	
ret_interrupt=request_irq(7,handler_irq,IRQF_SHARED,"parallelport","sam");
if(ret_interrupt==0)
{
//outb(16,0x037a);
printk(KERN_ALERT"success in request irq \n"); 
//outb(0x10,0x037a);
}
else
printk(KERN_ALERT"Fail in request irq \n"); 
//outb(0,0x0378);
//outb(16,0x037a);
//outb(16,0x037a);
	
return 0;
}
                 
int scull_open(struct inode *inodep,struct file *filep)
{

//unsigned long first,n;
//int ret_check;
//struct resource *ret_request;
//unsigned int i=0;
int dm_ret;
//int ret_interrupt;
unsigned int ret_inbs;
//unsigned int ret_inbd;
 scull_Dev=container_of(inodep->i_cdev,struct scull_dev,cDev);
                if(!scull_Dev)
                {
                        printk(KERN_ALERT"Fail in container mapping\n");
                }
                filep->private_data=scull_Dev;
  //first=START;
 // n = 3;	
dm_ret=driver_memory();
printk(KERN_INFO"dm_ret:%d\n",dm_ret);
//ret_inbs=inb(0x0379);
//printk("---64-----ret_inbs:%d \n",ret_inbs); 
//outb(16,0x037a);

ret_inbs=(inb(0x0379) & 64);
printk("-status:64-----ret_inbs:%d \n",ret_inbs); 

ret_inbd=inb(0x0378);
 
printk("data read on receiver out of interrupt ret_inbd:%d \t%c\n",ret_inbd,ret_inbd); 



/*

while(i<5)
{
outb(224,0x0378);
mdelay(1000);
outb(31,0x0378);
mdelay(1000);

i++;
}
*/
return 0;

}

irqreturn_t handler_irq(int signum,void *var)
{

//ret_inbd=(inb(0x0378) & 97);
ret_inbd=inb(0x0378);
printk("**************\n"); 
printk("data read on receiver ret_inbd:%d \t%c\n",ret_inbd,ret_inbd); 
printk("signum:%d argument var:%s \n",signum,(char*)var); 
	//tasklet_schedule(&short_tasklet);
return IRQ_HANDLED;
//outb(0,0x37a);
//return 0;
}

/*
void short_do_tasklet(unsigned long xvar)
{

ret_inbd=inb(0x0378);
printk("---64-----data read on receiver ret_inbd:%d \t%c\n",ret_inbd,ret_inbd); 

}

*/
int driver_memory(void)
{
int ret1=0,ret2=0;
int noq=3;
struct scull_dev *lsculldev;
struct scull_qset *lscullqset;
lsculldev=scull_Dev;
lsculldev->scull_Qset= NULL;
         lsculldev->scull_Qset= creat_scullqset();
        lscullqset=lsculldev->scull_Qset;
        if(lscullqset==NULL)
        {
          printk(KERN_INFO"No Scullqset to write\n");
        return 0;
        }

          printk(KERN_INFO" Scullqset address in write:%p\n",lscullqset);
          printk(KERN_INFO" Sculldev address in write:%p\n",lsculldev);

        ret1=creat_qset(lscullqset);
        if(ret1<0)
                printk(KERN_ALERT"failure in qset allocation \n");

	ret2=creat_quantum(lscullqset,noq);
        if(ret2<0)
                printk(KERN_ALERT"failure in quantum allocation \n");

return 0;
}



int creat_quantum(struct scull_qset *fscullqset,int fnoq)
{
        int i;
        if(!fscullqset)
                printk(KERN_ERR " error in create quantum-- unable to get scull_Qset starting address\n");
        else
        {       printk(KERN_ALERT " quantum created sucessfully\n");

                for(i=0;i<fnoq;i++)
                {       fscullqset->data[i]=NULL;
                  fscullqset->data[i]=kmalloc(scull_Dev->quantum_size,GFP_KERNEL);
                  memset(fscullqset->data[i],'\0',sizeof(fscullqset->data[i]));
			if(!fscullqset->data[i])
                        {
                                printk(KERN_INFO"kmalloc failure for i %d\n",i);
                                return -1;
                        }
           printk(KERN_ALERT"quantum %d address:%p\n ",i,(int *)fscullqset->data[i]);


                }
                       // fscullqset=fscullqset->next;
                       fscullqset->next=NULL;
        }
       
        
return 0;
}

int  creat_qset(struct scull_qset *fscullqset)
{
       
        if(!fscullqset)
        printk(KERN_ERR " error in create qset-- unable to get scull_Qset starting address\n");
        else
        {
          printk(KERN_ALERT " qset created sucessfully\n");
           fscullqset->data=NULL;
           fscullqset->data=kmalloc(sizeof(int *) * qset_size, GFP_KERNEL);
          if(!fscullqset->data)
          {
              printk(KERN_ERR"kmalloc failure at fsullqset->data for lv \n");
              return -1;
           }
 memset(fscullqset->data,'\0',sizeof(fscullqset->data));
           fscullqset->next=NULL;
                }
        
return 0;
}

struct scull_qset * creat_scullqset()
{
        struct scull_qset *start;
        
        start=NULL;
        start=(struct scull_qset *)(kmalloc(sizeof(struct scull_qset),GFP_KERNEL));
	if(!start)
        {
         printk(KERN_INFO"kmalloc failure scullqset \n");
         return NULL;
        }
      
	
	 memset(start,'\0',sizeof(start));
        printk(KERN_INFO"scullqset starting adress: %p\n",start);

               // start->next=NULL;
       // printk(KERN_ALERT"no of scullqsets:%d\n",fnosq);
	        
return start;
}


ssize_t scull_write(struct file *filep,const char __user *ubuff, size_t size, loff_t *loffp)
{
	struct scull_dev *lsculldev;
	struct scull_qset *lscullqset;
	size_t count=size;
//	char lbuff[]="tarun#";
	int ret1;
//	unsigned char ptr;
	lsculldev=(struct scull_dev *)filep->private_data;
        if(!lsculldev)
        {
                printk(KERN_ERR"ERROR:No ScullDev to write\n");
                return -1;
        }
                printk(KERN_INFO"count:%d\n",(int)count);
//ret3=copy_from_user(lscullqset->data[lv],ubuff+tnobsw,nobtw );
lscullqset=lsculldev->scull_Qset;
ret1=copy_from_user(lscullqset->data[0],ubuff,sizeof(ubuff) );

//printk(KERN_ALERT"Data in write:%s\n",(char *)lscullqset->data[0]);




//{
//outb(32,0x037a);
//var=0;
//outb(11,0x037a);
//var=var|4;
//outb(4,0x037a);
//outb('b',0x0378);
//ptr=inb(0x0378);
//printk(KERN_INFO "data received =%d\t%c\n",ptr,ptr);
//outb((int)lscullqset->data[0],0x0378);
//mdelay(1000);
//outb((int)lscullqset->data[0],0x0378);
//mdelay(1000);

//i++;
//}
return(ret1);
}

int scull_release(struct inode *inode,struct file *filep)
{

printk(KERN_INFO"scull closed\n");
return 0;
}

static void linuxworld_exit(void)
{
	free_irq(7,"sam");

        unregister_chrdev_region(dev,cm);
        printk(KERN_ALERT "unregistering mydriver\n");
        printk(KERN_ALERT "LINUXWORLD  Exit\n");
}
        module_init(linuxworld_init);
        module_exit(linuxworld_exit);


