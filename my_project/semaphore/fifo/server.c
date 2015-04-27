#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
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
	int i,fd1,fd2,file,recived,fork_result;
	int file_pipe[2];
	char buffer[2][2];
	if(access("fifo_server",F_OK == -1))
	file=mkfifo("fifo_server",0777);
	if(file<0)
	{
		printf("fifo not created successfuly");
		exit(-1);
	}
	else
	{
		printf("file created successfuly\n");
		printf("process pid is %d\n",getpid());
	}
	if(pipe(file_pipe)!=0)
	exit(-1);
	while(1)
	//for(i=0;i<3;i++)
	{
		fd1=open("fifo_server",O_RDONLY);
		recived=read(fd1,&datavar,sizeof(datavar));
		close(fd1);
		printf("number of bytes read are %d\n",recived);
		printf("read data is %c %d %d\n",datavar.arry,datavar.arr[0],datavar.arr[1]);
		recived=write(file_pipe[1],&datavar,sizeof(datavar));
		printf("number of bytes write are %d\n",recived);
		printf("write data is %c %d %d \n",datavar.arry,datavar.arr[0],datavar.arr[1]);
		fork_result=fork();
		switch(fork_result)
		{	
		case -1:
			printf("pipe not created succesfuly\n");
			break;
		case 0:
			printf("this is child process\n");
			printf("child pid is %d\n",getpid());
			sprintf(buffer[0],"%d",file_pipe[0]);
			sprintf(buffer[1],"%d",file_pipe[1]);
			printf("operator in buffer is %c\n",datavar.arry);
			if(datavar.arry=='+')
			{
			execl("pc1","pc1",buffer[0],buffer[1],(char *)0);
			}
			else if(datavar.arry=='-')
			{
			execl("pc2","pc2",buffer[0],buffer[1],(char *)0);
			}
			else if(datavar.arry=='*')
			{
			execl("pc3","pc3",buffer[0],buffer[1],(char *)0);
			}
			break;
		default:
			wait();
			printf("this is parrent process\n");
			printf("parrent pid is %d\n",getpid());
			recived=read(file_pipe[0],&datavar1,sizeof(datavar1));
			printf("number of bytes read are %d\n",recived);
			printf("data read is %c %d\n",datavar1.operator,datavar1.result);
			fd2=open("fifo_client1",O_WRONLY);
			printf("file discriptor is %d\n",fd2);
			recived=write(fd2,&datavar1,sizeof(datavar1));
			close(fd2);
			printf("number of byte write are %d\n",recived);
			printf("data write is %c %d\n",datavar1.operator,datavar1.result);
			//close(fd2);
			break;
		}
	}
	
}

