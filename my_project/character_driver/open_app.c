#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int a;
int b = 10;

int main()
{
	int rfd;
	char *ch1;

	printf("Address of bss = %p\n",&a);
	printf("Address of data = %p\n",&b);
	printf("Address of stack = %p\n",&rfd);
	
	ch1 = malloc(4096);
	strncpy(ch1,"lo World",12);
	printf("Heap Starts at %p\n",ch1);

	printf("PID of app is %d\n",getpid());

	rfd = open("my_nod",O_RDONLY);

	printf("PID of app is %d\n",getpid());

//	sleep(300);
	
	return 0;
}

