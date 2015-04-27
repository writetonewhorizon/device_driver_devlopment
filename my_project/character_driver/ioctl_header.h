#include<linux/ioctl.h>

#ifndef UNIQUE_MAGIC_NO
#define UNIQUE_MAGIC_NO 'K'
#endif

#define SCULL_RESET _IO(UNIQUE_MAGIC_NO,0)
#define SCULL_GQUANTUM _IOR(UNIQUE_MAGIC_NO,1,int)
#define SCULL_GDEVICE_SIZE _IOW(UNIQUE_MAGIC_NO,2,int)
#define SCULL_SQUANTUM _IOW(UNIQUE_MAGIC_NO,3,int)
