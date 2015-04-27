#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
int master_array(int fd);
char *mas_arr;
int code_length(int );
int compressed_array(int fd,int ndc,int cl);
char *com_arr;
int main()
{
	int fd,ndc,cl;
	fd=open("compress.h",O_RDONLY);
	if(fd<3)
	{
		printf("file not open successfully\n");
	}
	else
	{
		printf("file opened successfuly with fd = %d \n",fd);
	}
	ndc=master_array(fd);
	printf("number of distinct character are %d\n",ndc);
	cl=code_length(ndc);
	printf("code length is %d\n",cl);
	close(fd);
	fd=open("compress.h",O_RDONLY);
	compressed_array(fd,ndc,cl);
}
int master_array(int fd)
{
	int count,i=0,flag=0,j=0,sige=1;
	char ch;
	do
	{
		count=read(fd,&ch,sizeof(ch));
	//	printf("charactor read is %d %c \n",count,ch);
		if(i == 0)
		{
			mas_arr = (char * )malloc(sizeof(ch));
			if(mas_arr == 0)
			abort();
			memset(mas_arr,0,sizeof(char));
			*(mas_arr + i) = ch;
	//		printf("charactter in masterarray is %c\n",*mas_arr);
			i++;
		}
		else
		{	
		
			for(j=0;j<i;j++)
			{
				if(*(mas_arr + j)== ch)
				{
			//		printf("the value skiped is %c\n",ch);
					flag = 1;
					break;
				}
			}
			if(flag == 0)
			{
				mas_arr=realloc(mas_arr,++sige);
				*(mas_arr + i)=ch;
			//	printf("charactor in masterarry is %c\n",*(mas_arr + i));
				i++;
			}
			else
			{
				flag = 0;
				continue;
			}
		}
	}while(count==1);
	for(j=0;j<i-1;j++)
	{
		printf("master array is %d %c\n",j,*(mas_arr + j));
	}
	return(i-1);
}
int code_length(int ndc)
{
	int cl=0,i=1;
	if(ndc == 1)
	printf("code length is 1\n");
	while(ndc>i)
	{
		i=i*2;
		cl++;
	}
	return(cl);
}
int compressed_array(int fd,int ndc,int cl)
{
	int i,j,k=0,count,n=1;
	char ch,byte = 0,code = 0;
	do
	{
		byte=byte^byte;
		for(i=0;i<(cl/2);i++)
		{
			byte <<=cl;
			count=read(fd,&ch,1);
			for(j=0;j<=ndc;j++)
			{
				if(*(mas_arr + j)==ch)
				{
					code=j;
					break;
				}
			}
			byte=byte | code;
			//printf("byte = %x",byte);
		}
		if(k==0)
		{
		com_arr=(char * )malloc(1);
		*(com_arr + k)=byte;
	//	printf("%x\n",byte);
		k++;
		}
		else
		{
		com_arr=realloc(com_arr,++n);
		*(com_arr + k)=byte;
	//	printf("%x\n",byte);
		}
		k++;
	}while(count==1);
	for(j=0;j<k-1;j++)
	{
		printf("%x\n",*(com_arr + j));
	}
	return(j);

}
