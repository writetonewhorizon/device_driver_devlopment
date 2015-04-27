#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

int main(int argc,char *argv[])
{
	printf("<---------------Addition Process Program Started------------------>\n");
	int fdwrite,value1,value2,add[2],ret;
	fdwrite = atoi(argv[1]);
	value1 = atoi(argv[2]);
	value2 = atoi(argv[3]);
	//printf("ADDPROCESS: Values Received from Server : Val1 = %d Val2 = %d & PID = %d\n ",value1,value2,value3);
	
	add[0] = value1 + value2;
	printf("ADDPROCESS: Addition Result : %d + %d = %d\n",value1,value2,add[0]);
	ret = write(fdwrite,add,sizeof(int));
	printf("ADDPROCESS: Bytes Written to Server = %d\n",ret);
	printf("<----------------Addition Process Program Ended-------------------->\n");

	exit(0);
}
