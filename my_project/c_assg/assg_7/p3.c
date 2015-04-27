#include<stdio.h> 
int main()
{
	FILE *f;
	char buffer[11];
	if(f = fopen("fred.txt","rt"))
	{
		fread(buffer,1,10,f);
		buffer[10]=0;
		fclose(f);
		printf("first 10 character of the file :\n %s\n",buffer); 
	}
	return 0;
}
