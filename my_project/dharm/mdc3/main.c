#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
int master(int);
int code_length(int , int);
char *master_array;
int compress_file(int,int,int);
int main(int argc, char *argv[])
{
	int fd,nodc,cl,comp;
	fd=open("testfile.h",O_RDONLY);
	printf("fd = %d\n",fd);
	nodc=master(fd);
	printf("nodc = %d\n",nodc);
	printf("master_array = %s\n",master_array);
	cl = code_length(fd,nodc);
	printf("cl = %d\n",cl);
	close(fd);
	fd=open("testfile.h",O_RDONLY);
	printf("fd = %d\n",fd);
	comp = compress_file(fd, nodc,  cl);
	
return 0;
}
int master(int fd)
{
	unsigned char ch;
	int size=1,count=0,j=0,i=0,flag=0;
	printf("BEGIN : %s\n",__func__);
	master_array = (char *)malloc(size);
	printf("master_array = %p\n",master_array);
	do
	{
		count = read(fd,&ch,1);
		printf("count = %d\n",count);	
		for(j=0;j<=i;j++)
		{
			if(ch == *(master_array+j))
			{
				flag=1;
			}
			
		}
		if(flag == 0)
		{
			if(ch == '\n')
			{
				printf(" \n ");
			}
			else
			{
				
				*(master_array+i)=ch;
				printf("master_array = %s\n",master_array);
				i++;
				size++;
				j=0;
				master_array=(char *)realloc(master_array,size);
				printf("master_array = %p\n",master_array);
			}
		}
	flag=0;
	}while(count);
	printf("i = %d\n",i);
	printf("master_array = %s\n",master_array);
	printf("END : %s\n",__func__);
	return i;
}
int code_length(int fd, int nodc)
{
	int x=1,cl=0;
	
	printf("BEGIN : %s\n",__func__);
	if(nodc == 1)
	{
		cl = 1;
		goto out;
	}
	else
	{
		while(x < nodc)
		{
			x = x*2;
			cl++;
			printf("cl = %d\n",cl);
		}
	}
	printf("END : %s\n",__func__);
out:
	return cl;

}
int compress_file (int fd,int nodc,int cl)
{
	unsigned char byte,ch,ch1,temp;
                                                   
	int count=0,i=0,b=0,cnt=0,wfd;	
	printf("BEGIN : %s\n",__func__);
	wfd = open("write",O_WRONLY|O_APPEND);
	printf("wfd = %d\n",wfd);
	byte = byte^byte;
	printf("fd = %d, nodc = %d , cl = %d\n",fd,nodc,cl);
	printf("byte = %d\n",byte);
	printf("sizeof = %d\n",sizeof(byte));
	//do
	//{
	out:
		count = read(fd,&ch,1);
		printf("count = %d\n",count);
		printf("ch = %c\n",ch);
		for(i=0;i<nodc;i++)
		{
			if(ch==*(master_array+i))
			{
				if(b==0)
				{
					ch1 = i;
					printf("sizeof=%d and ch1= %c\n",sizeof(ch1),ch1);
					printf("i = %d\n",i);
					ch1=ch1 << 5;
					byte = byte | ch1;
					printf("byte= %d\n",byte);
					b++;
					goto out;
				}
				if(b==1)
				{
					ch1=i;
					printf("sizeof=%d and ch1= %c\n",sizeof(ch1),ch1);
					printf("i = %d\n",i);
					ch1=ch1<<5;
					ch1=ch1>>3;
					byte=byte |ch1;
					printf("byte= %d\n",byte);
					b++;
					goto out;
				}
				if(b==2)
				{
					temp = i;
					printf("sizeof=%d and ch1= %c\n",sizeof(ch1),ch1);
					printf("i = %d\n",i);
					ch1 = i+'0';
					printf("sizeof=%d and ch1= %c\n",sizeof(ch1),ch1);
					printf("i = %d\n",i);
					ch1 = ch1<<5;
					ch1 = ch1>>6;
					byte = byte |ch1;
					printf("byte= %d\n",byte);
					printf("wfd= %d\n",wfd);
					
					cnt = write(wfd,&byte,1);
					printf("sizeof=%d and temp= %c\n",sizeof(temp),temp);
					printf("i = %d\n",i);
					temp= temp << 7;
					byte = byte ^ byte;
					byte = byte | temp;
					printf("byte= %d\n",byte);
					printf("cnt = %d , byte = %d\n",cnt,byte);
					b++;
					goto out;
				}
				if(b==3)
				{
					ch1=i;
					printf("i=%d\n",i);	
					ch1=ch1<<5;
					ch1=ch1>>1;
					byte=byte | ch1;
					 printf("byte= %d\n",byte);
					b++;
					
					goto out;
				}
				if(b==4)
				{
					ch1=i;
					printf("sizeof=%d and ch1= %c\n",sizeof(ch1),ch1);
					printf("i = %d\n",i);
					ch1=ch1<<5;
					ch1=ch1>>4;
					byte=byte |ch1;
					printf("byte= %d\n",byte);
					b++;
					goto out;
				}
				if(b==5)
				{
					ch1 = i;
					printf("sizeof=%d and ch1= %c\n",sizeof(ch1),ch1);
					printf("i = %d\n",i);
					ch1 = ch1<<5;
					ch1 = ch1>>7;
					byte = byte |ch1;
					printf("byte= %d\n",byte);
					b++;
					goto out;
				}
				if(b==6)
				{
					
					temp = i;
					printf("sizeof=%d and ch1= %c\n",sizeof(ch1),ch1);
					printf("i = %d\n",i);
					ch1 = i+'0';
					printf("sizeof=%d and ch1= %c\n",sizeof(ch1),ch1);
					printf("i = %d\n",i);
					ch1 = ch1<<5;
					ch1 = ch1>>7;
					byte = byte |ch1;
					printf("byte= %d\n",byte);
				cnt = write(wfd,&byte,1);
					printf("cnt = %d , byte = %s\n",cnt,byte);
					b++;
					goto out;
				}
			}
		}

//	}while(count);
	printf("END : %s\n",__func__);
return wfd;
}
