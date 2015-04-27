#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>
#include<sys/sem.h>

#define MYSEM 9040
#define FIFO "myfifo"

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *buff;
};

