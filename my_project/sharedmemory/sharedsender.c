#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
struct my_sharing
{
	char my_text[512];
}*shared_stuff;
struct do_sharing
{
        char do_text[512];
	char result1[512];
}*proc_stuff;

int main()
{
	void *shared_memory=(void*) 0;
	void *proc_memory;
	int shmid1;
	int shmid;
	shmid=shmget(1234,sizeof(struct my_sharing),0666|IPC_CREAT);
	if(shmid==-1)
	{
		printf("shmget failed\n");
		exit(EXIT_FAILURE);
	}
	shared_memory=shmat(shmid,(void*)0,0);
/*	if(shared_memory==-1)
	{
		printf("shmat failed\n");
		exit(EXIT_FAILURE);
	}*/
	printf("memory attached at %x\n",shared_memory);
	shared_stuff=(struct my_sharing *)shared_memory;
        shmid1=shmget(1235,sizeof(struct do_sharing),0666|IPC_CREAT);
	printf("you wrote:%s",shared_stuff->my_text);
        proc_memory=shmat(shmid1,(void*)0,0);
        proc_stuff=(struct do_sharing*)proc_memory;
	strncpy(proc_stuff->do_text,shared_stuff->my_text,512);
	execl("procshare","procshare",NULL);
	printf("got the result=%s",proc_stuff->result1);
	exit(EXIT_SUCCESS);
}
