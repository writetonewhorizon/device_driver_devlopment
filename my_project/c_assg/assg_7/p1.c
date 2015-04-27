#include<stdio.h> 
int main()
{
	char buffer[100];
	FILE *f=fopen("rw.txt","r+");
	if(f)
	{
		fputc("some",f);
		fflush(f);
		fgets(buffer,9,f);
		printf("%s\n",buffer); 
		fclose(f);
	}
	return 0;
}
