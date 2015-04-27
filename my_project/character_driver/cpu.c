#define _GNU_SOURCE
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>

int i;

void func()
{
	int b = i;
	for(i=0; i<5; i++)
		func();
	if(i ==5)
	{
		i =0;
//		show_stack(NULL,NULL);
	}
}

int main()
{
	pid_t pid;
	cpu_set_t ptr;
	pid = getpid();


	CPU_ZERO(&ptr);
	CPU_SET(2,&ptr);
	printf("PID %d\n",pid);
	int i;
	for(i =0; i< 10000; i++)
	{
		printf("i am in defalut core\n");
		//sleep(1);
	}
	

	if(!sched_setaffinity(pid,1,&ptr))
		printf("i am in green core\n");

//	open("my_nod",O_RDONLY);
	while(1)
	{
	//	printf(" so rha hum main\n"); 
		//sleep(1);
	}


	func();

	show_stack(NULL,NULL);
	return 0;
}
