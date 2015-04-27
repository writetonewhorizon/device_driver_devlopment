#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char *argv[])
{
	int wfd,rfd;
	int len;
	int wc,rc;
	char *ch = "Vikram Sharma Attri jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj";
//	char *ch1 = "Sharma Attri ";
	char *ch2 = (char *)malloc(512);

	printf("BEGIN %s of app\n",__func__);

	wfd = open(argv[1],O_WRONLY);
	printf("Nod opened Successfully with fd = %d\n",wfd);
	
	len = strlen(ch);
	wc = write(wfd,ch,len);

	if(wc<0)
	{
		perror("write");
		return -1;
	}

	else if(wc == 0)
	{
		printf("Nothing Written\n");
		perror("write");
		return -1;
	}
	
	else if(wc > 0 && wc < len)
	{
		printf("Partially Written\n");
		return -1;
	}

	else if(wc == len)
	{
		printf("Write Succesfull with %d bytes Written\n",wc);
	}

	close(wfd);
		
//	len = strlen(ch1);
//	wfd = open(argv[1],O_WRONLY);
//	lseek(wfd,strlen(ch),SEEK_SET);
//	wc = write(wfd,ch1,len);
//	close(wfd);

	rfd = open(argv[1],O_RDONLY);
	lseek(rfd,20,SEEK_SET);
	rc = read(rfd,ch2,512);
	close(rfd);

	printf("Read from Device %s\n",ch2);
	memset(ch2,'\0',strlen(ch2));

	rfd = open(argv[1],O_RDONLY);
	lseek(rfd,0,SEEK_SET);
	rc = read(rfd,ch2,512);
	close(rfd);
	
	printf("Read from Device %s\n",ch2);

	printf("End %s of app\n",__func__);

	return 0;
}
	
