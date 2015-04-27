#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
int wfd,rfd;
int fd;
int len;
void *read_func(void *arg4)
{
	int seek_offset,count;
	printf("read_ rutine is working \n");
	char rbuff[225];
	memset(rbuff,'\0',sizeof(rbuff));
	seek_offset=lseek(rfd,6,SEEK_SET); 
        if(seek_offset<0)
        {
                printf("some error \n");
        }
        printf("seek_offset= %d\n",seek_offset);
	printf("len = %d\n",len);
        count=read(rfd,rbuff,len);
        printf("node read open successfully with fd=  %d\n",fd);
        printf("data read is %d   %s\n",count,rbuff);
        if(count<0)
        {
                printf("read %d\n",count);
        }
        else if(count==0)
        {
                printf("nothing read \n");
        }
        else if(count>0 && count<len)
        {
                printf("partialy read %d\n",count);
        }
        else if(count==len)
        {
                printf("read succesfully %d\n",count);
        }
	close(rfd);
}
void *open_read_func(void *arg3)
{
	printf("open_ rutine is working \n");
	printf("arg3 = %s\n",(char *)arg3);
	rfd = open((char *)arg3,O_RDONLY);
	if(rfd<0)
	{
	printf("error\n");
	}
	else
	{
		printf("rfd = %d\n",rfd);
	}
	pthread_exit((void *)&rfd);
}
void *write_func(void *arg2)
{
	int count;
	//char *ubuff="dharmender sharma ece/431/2009";
	char *ubuff="dharmender sharma ece/431/2009 888888888888888888888888888888888888855555555555555555555555555555555555555555555555558888888888888888888888888889999999999999999999999999999999999999999999999999999999999999999999999999999999";
	printf("write_ func is working \n");
	len = strlen(ubuff);
	printf("len = %d\n",len);
	count = write(wfd,ubuff,len);
	printf("count = %d ,ubuff = %s\n",count,ubuff);
	if(count<0)
	{
                printf("write %d\n",count);
        }
        else if(count==0)
        {
                printf("nothing write \n");
        }
        else if(count>0 && count<len)
        {
                printf("partialy write %d\n",count);
        }
        else if(count==len)
        {
                printf("writing succesfully %d\n",count);
        }
	
	close(wfd);
}
void *open_write_func(void *arg1)
{
	printf("open_ rutine is working \n");
	printf("arg1 = %s\n",(char *)arg1);
	wfd = open((char *)arg1,O_WRONLY);
	if(wfd<0)
	{
	printf("error\n");
	}
	else
	{
		printf("wfd = %d\n",wfd);
	}
	pthread_exit((void *)&wfd);
}
int main(int argc, char *argv[])
{
	int fd2;
	char *buffer=argv[1];
	pthread_t thread_ow,thread_or,thread_w,thread_r,thread_c;
	void *join1,*join2,*join3,*join4;
	if(argc<2)
	{
		printf("file not present\n");
	}
	printf("arg1 = %s\n",argv[1]);
	pthread_create(&thread_ow,0,&open_write_func,(void *)buffer);
	int retval = pthread_join(thread_ow,&join1);
	if(retval<0)
		printf("join1 error\n");
	printf("fd2 = %d\n",(int *)join1);
	
	pthread_create(&thread_w,0,&write_func,0);
	retval = pthread_join(thread_w,&join2);
	if(retval<0)
	printf("join2 error\n");
	
	pthread_create(&thread_or,0,&open_read_func,(void *)buffer);
	sleep(0);
	retval = pthread_join(thread_or,&join3);
	if(retval<0)
		printf("join3 error\n");	
	printf("fd2 = %d\n",(int *)join3);

	pthread_create(&thread_r,0,&read_func,0);
	retval = pthread_join(thread_r,&join4);
	if(retval<0)
	printf("join4 error\n");
	
	//pthread_create(&thread_c,0,&close_func,)
	return 0;
}
	
