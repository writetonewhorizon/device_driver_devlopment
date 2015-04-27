#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include"masterarray.c"
int master();
int main()
{
	char a[] = {"avtar singh khatdaa gtbkiet chhapianwali"};
	int fh,i = 0,count = 0;
	fh = open("origional5.txt",O_WRONLY | O_TRUNC);
	while(a[i] != '\0')
	{
		count++;
		i++;
	}
//	printf("array in main:%s\n",a);
	write(fh,a,count);
//	printf("count in main is %d\n",count);
	close(fh);
	master();
	return 0;
}
