#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>
union semun{
		int val;
		struct sem_id *buf;
		unsigned short *array;
		}arg;
int main()
{
	int sem_id;
	if((sem_id=semget(1234,1,0777 | IPC_CREAT)==-1);
	{
		printf("semaphore not created successfuly\n");
		exit(EXIT_FALUIRE);
	}
	else
	{
		printf("semaphore created successfuly\n");
		printf("semaphore semid is %d\n",sem_id);
	}

	
}
