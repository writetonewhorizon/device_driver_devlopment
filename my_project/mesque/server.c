#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<errno.h>
struct data{
		long int my_msg_type;
		char arry;
		int arr[2];
			};
struct data1{
		long int my_msg_type1;
		char operator;
		int result;
		};
int main()
{
	int msg_id,msg_id1,recived,fork_result,file_pipe[2];
	char buffer[2][2];
	struct data datavar;
	struct data1 datavar1;
	printf("making queue\n");
	msg_id= msgget(1234,0777 | IPC_CREAT);
	printf("msgid = %d\n",msg_id);
	if(msg_id== -1)
	{
		fprintf(stderr,"messege queue failed with error: %d\n", errno);
		exit(-1);
	}
	else 
	{
		printf("messege queue created successfuly\n");
	}
		recived=msgrcv(msg_id,&datavar,sizeof(datavar),1,0);
		printf("recived = %d\n",recived);
		printf("you recived : %c %d %d\n",datavar.arry,datavar.arr[0],datavar.arr[1]);
		printf("size of message %d\n",sizeof(datavar));
		msg_id1=msgget(1235,0777 | IPC_CREAT);
		printf("msgid1 = %d\n",msg_id1);
		if(msg_id == -1)
		{
		fprintf(stderr,"messege queue failed with error :%d\n",errno);
		exit(-1);
		}
		else
		{
		printf("messege queue created sucessfuly\n");
		}
		recived=msgsnd(msg_id1,&datavar,sizeof(datavar),0);
		printf("msgsnd = %d\n",recived);
		fork_result=fork();
		switch(fork_result)
		{
		case 0:
			printf("this is child\n");
			execl("pc1","pc1",(char *)0);
			break;
		default:
			wait();
			printf("this is parrent\n"); 
			recived=msgrcv(msg_id1,&datavar1,sizeof(datavar1),1,0);
			printf("msgrecived = %d\n",recived);
			printf("msgrecived %c %d\n",datavar1.operator,datavar1.result);
			recived=msgsnd(msg_id,&datavar1,sizeof(datavar1),0);
			printf("msgsnd = %d\n",recived);
			break;
		}
		/*recived=write(file_pipe[1],&datavar,sizeof(datavar));
		printf("wrote data %c %d %d\n",datavar.arry,datavar.arr[0],datavar.arr[1]);
		fork_result=fork();
		switch(fork_result)
		{
			case 0:
				printf("this is child and its pid is %d\n",getpid());
				sprintf(buffer[0],"%d",file_pipe[0]);
				sprintf(buffer[1],"%d",file_pipe[1]);
				printf("operator in buffer is %c\n",datavar.arry);
				if(datavar.arry=='+')
				{
					execl("pc1","pc11",buffer[0],buffer[1],(char *)0);
				}
				else if(datavar.arry=='-')
				{
					execl("pc2","pc2",(char *)0);
				}
				else if(datavar.arry=='*')
				{
					execl("pc3","pc3",(char *)0);
				}
				break;
			default :
				wait();
				printf("this is parrent and its pid is %d\n",getpid());
				recived=read(file_pipe[0],&datavar1,sizeof(datavar1));
				printf("data read = %d\n",recived);
				printf("data read  %c %d \n",datavar1.operator,datavar1.result);
				recived=msgsnd(msg_id,&datavar1,sizeof(datavar1),0);
				printf("msgsnd %c %d ",datavar1.operator,datavar1.result);
				break;
		}
	}*/
}

