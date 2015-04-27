#include"header.h"
int main()
{
	int server_fd,client_fd,recived;
	struct data dv;
	struct result dv1;
	dv.arr[0]='+';
	dv.arr[1]=20;
	dv.arr[2]=20;
	dv.client_pid=getpid();
	printf("program requisting client started  \n");
	server_fd=msgget(1234, 0666 | IPC_CREAT)== -1;
	if(server_fd == -1)
	{
		fprintf(stderr,"msget failed with error \n");
		exit(-1);
	}
	if(msgsnd(server_fd,&dv,sizeof(dv),0)== -1)
	{
		fprintf(stderr,"mssnd faild with error \n");
		exit(-1);
	}	
	client_fd=msgget(1235,0666 | IPC_CREAT);
	if(client_fd == -1)
	{
		printf(stderr,"msget failed with error \n");
		exit(-1);
	}
	if(msgrcv(client_fd,&dv1,sizeof(dv1),dv.client_pid,0)== -1);
	{
		printf(stderr,"msgrcv failed with error \n");
		exit(-1);
	}
	printf("client1 : result is (20+20)= %d\n",dv1.res);
	printf("end of program\n");
	exit(0);
}
