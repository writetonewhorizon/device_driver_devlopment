#include<stdio.h> 
#include<signal.h>
#include<stdlib.h> 
void sighup(int );
void sigint(int );
void sigquit(int );
int main()
{
	int pid;
/*	if( (pid = fork()) < 0)
	{
		printf("error");
		exit(1);
	}
	if(pid == 0)
	{*/
	pid = fork();
	switch (pid)
	{
	case -1:
		printf("error");
		exit(1);
		break;	
	case 0:
		printf("pid = %d\n",pid);
		signal(SIGINT,sighup);
		signal(SIGINT,sigint);
		signal(SIGQUIT,sigquit);
		for(;;)
		{
			printf("in for\n");
		}
		break;
//	}
//	if(pid > 0)
//	{
	default:
		printf("pid = %d\n",pid);
		printf("ppid= %d\n",getpid()); 
		printf("parrent sending SIGHUP\n"); 
//		kill(pid,SIGHUP);
		printf("pid = %d\n",pid);
		printf("ppid= %d\n",getpid()); 
		sleep(2);
		printf("parrent sending  SIGQUIT\n");
	//	kill(pid,SIGQUIT);
		sleep(2);
		break;
	}
	return 0;
}
void sighup(int x)
{
	printf("x=%d\n",x); 
//	signal(SIGHUP,sighup);
	printf("child i have recived a sighup\n"); 
		sleep(2);
}
void sigint(int x)
{
	printf("x=%d\n",x); 
//	signal(SIGINT,sigint);
	printf("child i have recived a sigint\n"); 
		sleep(2);
}
void sigquit(int x)
{
	printf("my daay has killed me\n");
	printf("x=%d\n",x); 
		sleep(2);
	exit(0);
}
