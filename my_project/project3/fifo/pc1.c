#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
struct data{
		char arry;
		int arr[2];
		}datavar;
struct data1{
		int result;
		char operator;
		}datavar1;
int main(int argc,char *argv[])
{
	int recived;
	int file_discriptor[2];
	printf("this is processing client1 \n");
	sscanf(argv[1],"%d",&file_discriptor[0]);
	printf("file discriptor is =%d \n",file_discriptor[0]);
	sscanf(argv[2],"%d",&file_discriptor[1]);
	printf("file discriptor is = %d \n",file_discriptor[1]);
	recived=read(file_discriptor[0],&datavar,sizeof(datavar));
	printf("read bytes are %d\n",recived);
	printf("read data is %c %d %d\n",datavar.arry,datavar.arr[0],datavar.arr[1]);
	datavar1.result=datavar.arr[0]+datavar.arr[1];
	printf("sum=%d\n",datavar1.result);
	datavar1.operator=datavar.arry;
	recived=write(file_discriptor[1],&datavar1,sizeof(datavar1));
	printf("number of bytes write are %d \n",recived);
	printf("data write is %c %d \n",datavar1.operator,datavar1.result);
	exit(0);
	
}
