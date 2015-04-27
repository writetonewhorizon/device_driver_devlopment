#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
	struct data{
			char arry;
			int aar[2];
		}datavar2;
	struct data1{
			char operator;
			int result;
			}datavar1;
void handler()
{
	unlink("fifo_process");
	unlink("fifo_client1");
	unlink("fifo_client2");
	unlink("fifo_client3");
}
int main()
{
	int file1,fd1,fd2,fd3,fd4,recived,i,j,arr[3];
	char buf[3][4];
	memset(buf,'\0',sizeof(buf));
	char buffer[2][2];
	memset(buffer,'\0',sizeof(buffer));
	pid_t fork_result;
	int file_pipe[2];
	if(access("fifo_process",F_OK) == -1)
	file1 = mkfifo("fifo_process",0777);
        if(file1 < 0)
        {
		 printf(".....Unable to create a fifo");
		 exit(-1);
	}
	else
	{	
		printf("fifo is created successfully\n");
		printf("pid of process is %d\n",getpid());
	}
	fd1=open("fifo_process",O_RDONLY);

	if(pipe(file_pipe)!=0)
		exit(-1);
	signal(13,handler);
	while(1)
	{
again:	recived=read(fd1,&datavar2,sizeof(datavar2));
	if(recived == 0)
		goto again;
	printf("%c %d %d \n",datavar2.arry,datavar2.aar[0],datavar2.aar[1]);
		printf("******i = %d\n",i);
		recived=write(file_pipe[1],&datavar2,sizeof(datavar2));
		printf(".........%d.......\n",recived);
	printf("...%c %d %d \n",datavar2.arry,datavar2.aar[0],datavar2.aar[1]);
		recived=read(file_pipe[0],&datavar2,sizeof(datavar2));
	printf("%c %d %d \n",datavar2.arry,datavar2.aar[0],datavar2.aar[1]);
		recived=write(file_pipe[1],&datavar2,sizeof(datavar2));
		printf("number of bytes write in pipe are %d\n",recived);
			fork_result=fork();
			switch(fork_result)
			{
			case-1:
				printf("pipe is not created successfuly");
				break;
			case 0:
				printf("this is child :\n");
				printf("child pid is %d\n",getpid());
				sprintf(buffer[0],"%d",file_pipe[0]);
				sprintf(buffer[1],"%d",file_pipe[1]);
				printf("operator in buffer is = %c\n",datavar2.arry);
				printf("---%s----%s----\n",buffer[0],buffer[1]);
				if(datavar2.arry == '+')
				{
                                execl("rc1","rc1",buffer[0],buffer[1],(char *)0);
				}
				else if(datavar2.arry == '-')
				{						
                                execl("rc2","rc2",buffer[0],buffer[1],(char *)0);
				}			
				else if(datavar2.arry == '*')
				{						
                                execl("rc3","rc3",buffer[0],buffer[1],(char *)0);
				}
			default:
				wait();
				printf("this is parrent:\n");
			//	printf("parrent pid is %d\n",getpid());
				//wait();
				recived=read(file_pipe[0],&datavar1,sizeof(datavar1));
				printf("read bytes are %c %d\n",datavar1.operator,datavar1.result);
			//	wait();
				//printf("%s\n",buf[0]);
				//printf("**********");
				
				if(datavar1.operator == '+')
				{
					printf("in the if\n");
				fd2=open("fifo_client1",O_WRONLY);
				printf("file discriptor is %d\n",fd2);
				recived=write(fd2,&datavar1,sizeof(datavar1));
				printf("writes bytes are %c %d\n",datavar1.operator,datavar1.result);
				
				printf("number of write bytes are %d\n",recived);
				}
				else if(datavar1.operator == '-')
				{
				fd3=open("fifo_client2",O_WRONLY);
				printf("file discriptor is %d\n",fd3);
				recived=write(fd3,&datavar1,sizeof(datavar1));
				printf("number of writes bytes are %d\n",recived);
				}
				else if(datavar1.operator == '*')
				{
				fd4=open("fifo_client3",O_WRONLY);	
				printf("file discriptor is %d\n",fd4);
				recived=write(fd4,&datavar1,sizeof(datavar1));
				printf("number of writes bytes are %d\n",recived);
				}
				break;
			}
		}
	
}
