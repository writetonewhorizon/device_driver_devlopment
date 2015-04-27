#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include"ioctl_header.h"

int main(int argc, char *argv[])
{
	int fd;
	int quantum_size;
	int *arg;
	int arg1;

	arg = &arg1;

	printf("arg = %p\n",arg);

	fd = open(argv[1],O_RDONLY);

	ioctl(fd,SCULL_RESET);

	ioctl(fd,SCULL_GQUANTUM,&arg1);

	printf("quantum_size = %d\n",arg1);

	arg1 = 16;

	quantum_size = ioctl(fd,SCULL_SQUANTUM,arg);
	
	printf("New quantum_size = %d\n",quantum_size);
	
	close(fd);

	return 0;
}
