#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc,char *argv[])
{
	printf("START:%s\n",__func__);
	char *buffer = "AVTAR IS GOOD PERSON";
	char buffer1 = 1;
	int fd;
	int retval = 0;
	if(argc == 1)
	{
		printf("Enter file name as command line arguments\n");
		goto RET;
	}
	else
	{
		fd = open(argv[1],O_WRONLY);
		printf("fd = %d\n",fd);
		retval = write(fd,buffer,20);
		printf("Successfully written %d BYTES\n",retval);
	}
	printf("END:%s\n",__func__);
	return 0;
RET:
	printf("END E:%s\n",__func__);
	return -1;
}
