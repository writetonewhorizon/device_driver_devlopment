#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include"masterarray.c"
int master();
int main()
{
	char a[] = {"avtar singh khatdaa gtbkiet chhapianwali"};
	char h;
	int fh,i = 0,count = 0;
	fh = open("origionalg.txt",O_WRONLY);
	while(a[i] != '\0')
	{
		count++;
		i++;
	}
	write(fh,&a,count);
	printf("count in main is %d\n",count);
	close(fh);
	master();
	
	return 0;


}
