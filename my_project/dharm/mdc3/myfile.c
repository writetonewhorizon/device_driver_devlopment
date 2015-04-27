#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{
	int rfd,count;
	char array[40];
	memset(array,'\0',sizeof(array));
	rfd = open("main.c",O_RDONLY);
	count= read(rfd,array,1);
	printf("count = %d , array = %s\n",count,array);
	close(rfd);
return 0;
}
