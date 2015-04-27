#include<stdio.h> 
#include<signal.h>
#include<stdlib.h>
void sigproc(int);
void quitproc(int);
int main()
{
	signal(SIGINT,sigproc);
	//signal will call the function sigproc when it will recive a signal SIGINT
	signal(SIGQUIT,quitproc);
	printf("ctrl+c disabled use \n"); 
	for(;;);
return 0;
}
void sigproc(int x)
{
	printf("x=%d\n",x); 
	signal(SIGINT,sigproc);
	printf("you have pressed ctrl+c\n"); 
}
void quitproc(int x)
{
	printf("x=%d\n",x);	
	printf("ctrl-\\pressed to quit\n");
	exit (0);
}
