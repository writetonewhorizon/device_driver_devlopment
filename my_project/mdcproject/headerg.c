#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include"masterarrayg.c"
int masterarr();
int main()
{
	char a[] = {"my name is Avtar SINGH Khatdaa"};
	int fh,i = 0,count = 0;
	fh = open("origionalg.txt",O_WRONLY | O_TRUNC);
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
