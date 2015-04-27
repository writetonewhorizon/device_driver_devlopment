#include<stdio.h> 
#include<stdlib.h>
#include<unistd.h> 
#include<linux/limits.h> 
int main()
{
	printf(" running ps with execlp \n");
	printf("pid= %d and ARG_MAX = %d\n",getpid,ARG_MAX); 
	execlp("ps","ps","aux", 0);
	printf("pid= %d\n",getpid); 
	printf("Done\n");
	exit(0);
}
