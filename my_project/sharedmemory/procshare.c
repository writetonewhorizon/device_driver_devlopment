#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
struct do_sharing
{
        char do_text[512];
	char result1[512];
}*proc_stuff;

int main()
{
	int operand[2],result;
	char operator,buffer[10];
	void *proc_memory;
	int shmid1;
	shmid1=shmget(1235,sizeof(struct do_sharing),0666|IPC_CREAT);
	proc_memory=shmat(shmid1,(void*)0,0);
	printf("memory attached at %x\n",proc_memory);
	proc_stuff=(struct do_sharing*)proc_memory;
	printf("we got=%s\n",proc_stuff->do_text);
	sscanf(proc_stuff->do_text,"%d %d %c",&operand[0],&operand[1],&operator);
	result=operand[0]+operand[1];
	sprintf(buffer,"%d",result);
	printf("result=%d",result);
	strcpy(proc_stuff->result1,buffer);
	printf("written result=%s",proc_stuff->result1);
}
