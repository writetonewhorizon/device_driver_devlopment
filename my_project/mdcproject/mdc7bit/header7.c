#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include"masterarray7.c"
int masterarr();
int main()
{
	char a[] = {"abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ !@#$%^&*()abcdefgh"};
	int fh,i = 0,count = 0;
	fh = open("origional7.txt",O_WRONLY | O_TRUNC);
	while(a[i] != '\0')
	{
		count++;
		i++;
	}
	write(fh,a,count);
	close(fh);
	masterarr();
	return 0;
}
