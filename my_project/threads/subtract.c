#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

int main(int argc,char *argv[])
{
	printf("<---------------Subtraction Process Program Started------------------>\n");
	int fdwrite,value1,value2,sub[2],ret;
	fdwrite = atoi(argv[1]);
	value1 = atoi(argv[2]);
	value2 = atoi(argv[3]);
	
	sub[0] = (value1 - value2);
	printf("SUBPROCESS: Result : %d - %d = %d\n",value1,value2,sub[0] );
	ret = write(fdwrite,sub,sizeof(int));
	printf("SUBPROCESS: Bytes Written to Server = %d\n",ret);
	printf("<----------------Subtraction Process Program Ended-------------------->\n");

	return 0;
}
