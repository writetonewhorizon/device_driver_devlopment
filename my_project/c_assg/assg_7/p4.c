#include<stdio.h> 
int main()
{
	FILE *f;
	f=fopen("myfile.txt","w");
	fputs("helloworld",f);
	fseek(f,6,SEEK_SET);
	fputs("india",f);
	fclose(f);
	return 0;
}
