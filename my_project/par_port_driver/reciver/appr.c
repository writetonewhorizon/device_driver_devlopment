#include<stdio.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
	int fd;
	char buffer;
	fd = open(argv[1],O_RDONLY);
	printf("fd = %d\n",fd);
	read(fd,buffer,sizeof(buffer));
	printf("%c\n",buffer); 
}
