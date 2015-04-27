#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
	FILE *file;

	char *ch = "Vikram Sharma Attri";
	void *ch1 = malloc(20);

	file = fopen(argv[1],"r+");

	printf("file in process = %x\n",file);

//	fwrite((const void *)ch,1,strlen(ch),file);
//	fread(ch1,1,strlen(ch),file);

//	printf("Read  %s\n",ch1);

	return 0;

}

	
