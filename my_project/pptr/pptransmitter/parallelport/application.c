#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/ioctl.h>
int main(int argc,char *argv[])
{
int fd,ret_w;
fd=open(argv[1],O_WRONLY);
if(fd<0)
printf("fail to open\n");
printf("fd:%d\n",fd);
//sleep(5);
ret_w=write(fd,"97",3);
if(ret_w<0)
printf("fail to write\n");
if(ret_w==0)
printf("sucess in writing\n");

close(fd);
}
