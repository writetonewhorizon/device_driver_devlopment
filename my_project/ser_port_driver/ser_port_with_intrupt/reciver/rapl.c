#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc,char *argv[])
{
	printf("START:%s\n",__func__);
	char buffer[20];
	int fd;
	int retval = 0;
	if(argc == 1)
	{
		printf("Enter file name as command line arguments\n");
		goto RET;
	}
	else
	{
		fd = open(argv[1],O_RDONLY);
		printf("fd = %d\n",fd);
		retval = read(fd,buffer,20);
		printf("Successfully written %d BYTES\n",retval);
	}
	printf("DATA = %s\n",buffer);
	printf("END:%s\n",__func__);
	return 0;
RET:
	printf("END E:%s\n",__func__);
	return -1;
}
