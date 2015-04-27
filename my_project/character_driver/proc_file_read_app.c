#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(int argc,char *argv[])
{
	int fd;
	int rc;

	char *ch = (char *)malloc(100);

	int data;
	if(argc < 2)
		printf("Too few Arguments...Provide file name\n");

	fd = open(argv[1],O_RDONLY);
	if(fd > 0)
		printf("%s opened with fd = %d\n",argv[1],fd);

	rc = read(fd,ch,100);
		printf("Read returned rc = %d\n",rc);
//		printf("%s\n",ch);

	rc = read(fd,ch+strlen(ch),100);
		printf("Read returned rc = %d\n",rc);
		printf("%s\n",ch);

	return 0;
}
