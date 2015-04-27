#include<stdio.h>
#include<fcntl.h>
#include<string.h>
int main(int argc, char *argv[])
{
	int fd,fd1,fd2,fd3,len,count,seek_offset;
	char *ubuff="dharmender sharma ece 431 2009 555555555555555555555555555555555555ramayan5555555555555555555mahabhart5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555";
	//char *ubuff="dharmender sharma 44444444444444444444444444444444444444444447777777777777777777777777"; 
	char *u1buff =  "dharmender sharma mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm";
	char rbuff[1000];
	char r1buff[200];
	memset(rbuff,'\0',sizeof(rbuff));
	fd=open(argv[1],O_WRONLY);
	if(argc<2)
	{
		printf("file not open successfully\n");
	}
	printf("node open successfully with fd=  %d\n",fd);
	len = strlen(ubuff);
	printf("len=%d\n",len);
	count=write(fd,ubuff,len);
	printf(" len = %d ,count =  %d ,ubuff = %s\n",len,count,ubuff);
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
	/*len=strlen(u1buff);
	printf("len=%d\n",len);
	count=write(fd,u1buff,len);
	printf(" len = %d ,count =  %d ,ubuff = %s\n",len,count,ubuff);
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
	}*/
	sleep(1);
	close(fd);
	
	fd1=open(argv[1],O_RDONLY);
	seek_offset = lseek(fd,130,SEEK_SET);
	if(seek_offset<0)
	{
		printf("some error \n");
	}
	printf("seek_offset= %d\n",seek_offset);
	count=read(fd1,rbuff,len);
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
	close(fd1);
	

	fd2=open(argv[1],O_WRONLY);
	if(argc<2)
	{
		printf("file not open successfully\n");
	}
	printf("node open successfully with fd=  %d\n",fd2);
	len = strlen(u1buff);
	printf("len=%d\n",len);
	count=write(fd2,u1buff,len);
	printf(" len = %d ,count =  %d ,ubuff = %s\n",len,count,u1buff);
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
close(fd2);
	fd3=open(argv[1],O_RDONLY);
	seek_offset = lseek(fd3,30,SEEK_SET);
	if(seek_offset<0)
	{
		printf("some error \n");
	}
	printf("seek_offset= %d\n",seek_offset);
	count=read(fd3,r1buff,len);
	printf("node read open successfully with fd=  %d\n",fd3);
	printf("data read is %d   %s\n",count,r1buff);
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
	close(fd3);
return 0;
}
	
