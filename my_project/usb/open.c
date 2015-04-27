#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int fd;
	fd = open("/dev/my_node",O_RDONLY);

	return 0;
}
	
