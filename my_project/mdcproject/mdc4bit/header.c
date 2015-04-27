#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include"masterarray.c"
#include"compression_opr.c"
int master(int);
int compress();
int main()

{
	char a[] = {"she sells the sea shells on the sea shore"};
//	FILE *fp;
//	fp = fopen("singh.c","r+");
//	fputs(a,fp);
//	fclose(fp);
	int fp,b,count = 0,i = 0;
	char m;
	m = a[0];
	while(m != '\0')
	{
		count++;
		m = a[i];

	}
	fp = open("singh.c",O_WRONLY);
	b = write(fp,&a,count);
//	fp = puts(a);
	close(fp);
	master(count);
	compress();
	return 0;
}
