#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc,char *argv[])
{
	int fd;
	fd = open(argv[1],O_RDONLY);

	if(!fork())
		open(argv[1],O_WRONLY);

	return 0;
}
