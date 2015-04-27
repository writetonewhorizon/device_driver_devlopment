#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
        int fd1,fd4,i,file1,recived;
        int arr2[3];
        char arry[3][4];
        struct data{
                        char arr1;
                        int arr[2];
                }datavar;
	struct data1{
			char oprator;
			int result;
			}datavar1;
        datavar.arr1='*';
        datavar.arr[0]=20;
        datavar.arr[1]=20;
        fd1=open("fifo_process",O_WRONLY);
        printf("file discriptor is %d\n",fd1);
        printf("process pid is %d\n",getpid());
//        sprintf(arr1,"%d%c%d",arr[1],arr[0],arr[2]);
                recived=write(fd1,&datavar,sizeof(datavar));
		printf("%c %d %d\n",datavar.arr1,datavar.arr[0],datavar.arr[1]);
        printf("written byte are= %d \n",recived);
        if(access("fifo_client3",F_OK==-1))
        file1=mkfifo("fifo_client3",0777);
        if(file1<0)
        {
                printf("enable to create fifo");
                exit(-1);
        }
        else
        {
                printf("file create successfuly\n");
                printf("pid of process is %d\n",getpid());
        }
        fd4=open("fifo_client3",O_RDONLY);
        printf("file discriptor is %d\n",fd4);
     //   sleep(2);
        recived=read(fd4,&datavar1,sizeof(datavar1));
        printf("number of bytes read are= %d\n",recived);
	printf("client3 (20*10)result = %d\n",datavar1.result);
        printf("end of program\n");
}

