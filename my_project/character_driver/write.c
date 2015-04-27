#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int fd,wr;
	fd = open("my_node",O_WRONLY);

	wr=write(fd,"abcde",5);
	return 0;
}
