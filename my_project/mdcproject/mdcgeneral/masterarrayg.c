//#include<stdio.h>
//#include<unistd.h>
//#include<fcntl.h>
#include"compression3.c"
int compress(int,int);
int master()
{
	int fm,fo,i,j,g = 0,count = -1,mcount = 0,rc = 1;
	char k;
	fo = open("origional.txt",O_RDONLY);
	fm = open("masterarray3.txt",O_WRONLY);
	read(fo,&k,1);
	while(rc != 0)
	{
		count++;
		rc = read(fo,&k,1);
	}
	char org[count];
	printf("count in master() is %d\n",count);
	lseek(fo,SEEK_SET,0);
	read(fo,&org,count);
//	printf("%c\n",org[2]);
	for(i = 0;i < count;i++)
	{
		g++;
		k = org[i];
		if(i == 0)
		{
			write(fm,&k,1);
			mcount++;
		}
		else
		{
		for(j = 0;j < g-1;j++)
		{
			if(k == org[j])
			{
				break;
			}
			else if(j == g - 2)
			{
				write(fm,&k,1);
				mcount++;
			}
			else
				continue;
		}
//		write(fm,&k,1);
		}
	}
	printf("value of mcount is %d\n",mcount);
	compress(count,mcount);
	return(1);
}
