#include<stdio.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
	int fd;
	char buffer='A';
	fd = open(argv[1],O_WRONLY);
	printf("fd = %d\n",fd);
	write(fd,buffer,sizeof(buffer));
}
