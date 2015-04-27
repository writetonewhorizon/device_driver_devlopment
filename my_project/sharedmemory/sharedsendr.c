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
int main()
{
        void *shared_memory=(void*)0;
	int operand[2];
	char operator='+';
        char buffer[512];
	int shmid;
        shmid=shmget((key_t)1234,sizeof(struct my_sharing),0666|IPC_CREAT);
        if(shmid==-1)
        {
                printf("shmget failed\n");
                exit(EXIT_FAILURE);
        }
	printf("shmid=%d",shmid);
        shared_memory = shmat(shmid,(void *) 0,SHM_RND);
     /*   if(*shared_memory=-1)
	{
                printf("shmat failed\n");
                exit(EXIT_FAILURE);
        }*/
	shared_stuff=(struct my_sharing*)shared_memory;
        printf("memory attached at %x\n",shared_memory);
/*	printf("enter some text:\n");
	scanf("%s",&buffer);*/
	operand[0]=5;
	operand[1]=3;
	operator='+';
	sprintf(buffer,"%d %d %c",operand[0],operand[1],operator);
	strcpy(shared_stuff->my_text,buffer);
	sleep(5);
	exit(EXIT_SUCCESS);


}
