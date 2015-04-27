#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include"masterarray3.c"
int master();
int main()
{
	char a[] = {"old is gold is old"};
	char h,x = EOF;
	int fh,i = 0,count = 0;
	fh = open("origional.txt",O_WRONLY);
	while(a[i] != '\0')
	{
		count++;
		i++;
	}
	write(fh,&a,count);
//	write(fh,&x,1);
	printf("count in maim is %d\n",count);
/*	close(fh);
	count = 0;
	fh = open("origional.txt",O_RDONLY);
	read(fh,&h,1);
	while(h != EOF)
	{
		count++;
		read(fh,&h,1);
	}
	printf("%d\n",count);*/
	close(fh);
//	masterarr();
	master();
	
	return 0;


}
