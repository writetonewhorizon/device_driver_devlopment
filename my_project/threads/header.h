#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<ctype.h>
#include<pthread.h>
#define SERVER_FIFO "/home/dharmender/threads/server_fifo"
#define CLIENT_FIFO "/home/dharmender/threads/cli_%d_fifo"

struct database
{
	pid_t client_pid;
	int data[4];
};
