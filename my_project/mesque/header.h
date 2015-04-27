#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<limits.h>
#include<fcntl.h>
#include<ctype.h>
struct data{
		long int client_pid;
		int arr[4];
		};
struct result{
		long int client_pid;
		int res;
		};
