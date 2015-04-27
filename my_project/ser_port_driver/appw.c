#include<stdio.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
	int fd;
	char buffer='A';
	fd = open(argv[1],O_WRONLY);
	printf("fd = %d\n",fd);
	fd = write(fd,&buffer,1);
	printf("write data on kernal is %c\n",buffer);
	printf("fd = %d\n",fd);
	return 0;
}
