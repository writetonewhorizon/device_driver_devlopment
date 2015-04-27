#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

int main(int argc,char *argv[])
{
	printf("<---------------Multiply Process Program Started------------------>\n");
	int fdwrite,value1,value2,mul[2],ret;
	fdwrite = atoi(argv[1]);
	value1 = atoi(argv[2]);
	value2 = atoi(argv[3]);
	mul[0] = value1 * value2;
	printf("MULPROCESS: Result : %d * %d = %d\n",value1,value2,mul[0]);
	ret = write(fdwrite,mul,sizeof(int));
	printf("MULPROCESS: Bytes Written to Server = %d\n",ret);
	printf("<----------------Multiply Process Program Ended-------------------->\n");

	return 0;
}
