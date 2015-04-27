#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
struct data{
		char arry;
		int arr[2];
		}datavar;
struct data1{
		int result;
		char operator;
		}datavar1;
int main()
{
	int fd1,fd2,file1,recived;
	datavar.arry='*';
	datavar.arr[0]=20;
	datavar.arr[1]=20;
	fd1=open("fifo_server",O_WRONLY);
	printf("process pid is %d\n",getpid());
	recived=write(fd1,&datavar,sizeof(datavar));
	close(fd1);
	printf("number of written by are %d\n",recived);
	printf("writen data is %c %d %d\n",datavar.arry,datavar.arr[0],datavar.arr[1]);
	if(access("fifo_client1",F_OK) == -1)
	file1=mkfifo("fifo_client1",0777);
	if(file1<0)
	{
		printf("file not created successfuly\n");
	}
	else
	{
		printf("file created successfully and pid is %d\n",getpid());
	}
	fd2=open("fifo_client1",O_RDONLY);
	printf("file discriptor is %d\n",fd2);
	recived=read(fd2,&datavar1,sizeof(datavar));
	close(fd2);
	printf("number of bytes read are %d\n",recived);
	printf("result of multiplication is  (20*20)= %d\n",datavar1.result);
	printf("end of program\n");
}
