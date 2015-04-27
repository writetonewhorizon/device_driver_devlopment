#include<stdio.h>
#include<stdlib.h> 
int main()
{
	system ("ps -al");
	system ("ps -al");
	printf("Done\n"); 
	printf("Done");
	printf("%d",getpid());
	sleep(5);
	printf("Done"); 
	sleep(5);
	printf("Done"); 
	return 0;
}
