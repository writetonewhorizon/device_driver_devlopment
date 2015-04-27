#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/ipc.h>
#include<sys/msg.h>
struct data{	long my_msg_type;
		char arry;
		int arr[2];
		};
struct data1{
		long my_msg_type1;
		int result;
		char operator;
		};
int main(int argc,char *argv[])
{
	int recived,msg_id1;
	struct data datavar;
	struct data1 datavar1;
	printf("this is client1\n");
	msg_id1=msgget(1235,0777 | IPC_CREAT);
	printf("msgid = %d\n",msg_id1);
	recived=msgrcv(msg_id1,&datavar,sizeof(datavar),1,0);
	printf("recived data is %d\n",recived);
	printf("messege read is %c %d %d\n",datavar.arry,datavar.arr[0],datavar.arr[1]);
	datavar1.result=datavar.arr[0]-datavar.arr[1];
	datavar1.operator=datavar.arry;
	datavar1.my_msg_type1=1;
	printf("differance = %d\n",datavar1.result);
	recived=msgsnd(msg_id1,&datavar1,sizeof(datavar1),0);
	printf("msgsnd = %d\n",recived);
	printf("msgsnd %c %d\n",datavar1.operator,datavar1.result);
	exit(1);
}
