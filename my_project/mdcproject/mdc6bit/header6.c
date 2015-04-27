#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include"masterarray6.c"
int masterarr();
int main()
{
	char a[] = {"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"};
	int fh,i = 0,count = 0;
	fh = open("origional6.txt",O_WRONLY | O_TRUNC);
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
