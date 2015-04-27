#include<stdio.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char *argv[])
{
	int fd,count = 0,len,ret;
	char data3[8];
//	char data[] = "Emblogic Embedded Technologies Pvt. Ltd avtar singh khatdaa vikram sharma attri om parkash singhania prince singla kushal chugh noida uttar pradesh india pin 201301";
	char data[] = "Emblogic Embedded Technologies Pvt. Ltd Noida xxxxxxxxxxxxxxxxxxxxxxxxxyyyyyyyyyyyyyyyyyyyyyyyyyyyzzzzzzzzzzzzzzzz";
	char data1[] = "88888888888888**************9999999999000000000000000000000000000aaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbssssssssssssssssssssssssscccccccccccccccccccccccccccccccddddddddddddddddddddddddddddddeeeeeeeeeeeeeeee";
//	char data1[] = "**************9999999999000000000000000000000000000aaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbssssssssssssssssssssssssscccccccccccccccccccccccccccccccddddddddddddddddddddddddddddddeeeeeeeeeeeeeeee";
//	char rbuff[20];
	if(argc == 2)
	{
		fd = open(argv[1],O_RDONLY);
		printf("File open successfully with fd = %d\n",fd);
	}
	else
	{
		printf("Please Enter file name.\n");
		return -1;
	}
//	ret = lseek(fd,8,SEEK_SET);
//	printf("lseek position = %d\n",ret);
	len = strlen(data3);
	count = read(fd,data3,len);
	if(count < 0)
	{
		printf("Nothing written by driver\n");
		goto OUT;
	}
	else if(count == 0)
	{
		printf("Nothing to read\n");
		printf("data = %s\n",data3);
		goto END;
	}
	else if(count > 0 && count < len)
	{
		printf("Partially written count = %d\n",count);
		printf("data = %s\n",data3);
	}
	else if(count == len)
	{
		printf("No. of bytes Succesfully written = %d\n",count);
		printf("data = %s\n",data3);
	}
	close(fd);
//	fd = open(argv[1],O_WRONLY);
//	printf("Open successfully with fd = %d\n",fd);
/*	ret = lseek(fd,10,SEEK_SET);
	printf("lseek position = %d\n",ret);
	len = strlen(data1);
	count = write(fd,data1,len);
	if(count < 0)
	{
		printf("Nothing written by driver\n");
		goto OUT;
	}
	else if(count == 0)
	{
		printf("Nothing to write\n");
	}
	else if(count > 0 && count < len)
	{
		printf("Partially written count = %d\n",count);
		printf("data1 = %s\n",data1);
	}
	else if(count == len)
	{
		printf("No. of bytes Succesfully written = %d\n",count);
		printf("data1 = %s\n",data1);
	}
	close(fd);
	fd = open(argv[1],O_RDONLY);
//	ret = lseek(fd,20,SEEK_SET);
	printf("lseek position = %d\n",ret);
	len = sizeof(data3);
	memset(data3,'\0',len);
	count = read(fd,data3,len);
	if(count < 0)
	{
		printf("Nothing read\n");
		goto OUT;
	}
	else if(count == 0)
	{
		printf("Nothing to read\n");
//		goto END;
	}
	else if(count > 0 && count < len)
	{
		printf("Partially read\n");
		printf("No. of bytes Succesfully read = %d\n",count);
		printf("data3 = %s\n",data3);
		goto PAR;
	}
	else if(count == len)
	{
		printf("No. of bytes Succesfully read = %d\n",count);
	}
	printf("data = %s\n",data3);*/
//	close(fd);
	printf("End:%s\n",__func__);
	return count;
PAR:
	printf("End:%s\n",__func__);
	return count;
END:
	printf("End:%s\n",__func__);
	return count;
OUT:
	printf("End E:%s\n",__func__);

	return -1;
}
