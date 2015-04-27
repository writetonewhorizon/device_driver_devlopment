#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h> 
int main()
{
	int n,i;
	char *message;
	int pid;
	pid = fork();
	switch (pid)
	{
	case -1:
		printf("Fork failed\n");
		break;
	case 0:
		message="This is child";
		printf("child pid=%d\n",getpid());
		n=3;
		break;
	default :
		message="This is parent";
		printf("parrent pid=%d\n",getpid());
		n=5;
		break;
	}
	for(i=0;i<n;i++)
	{
		puts(message);
		printf(" pid=%d\n",getpid());
		sleep(1);
	}
	return 0;
}
