#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include"masterarray.c"
int master();
int main()
{
	char a[] = {"avtar singh khatdaa gtbkiet chhapianwali"};
	int i = 0,j,count = 0,fo,rc,mcount = 0;
	char *ch,k;
	while(a[i] != '\0')
	{
		count++;
		i++;
	}
	fo = open("origionalg.txt",O_RDWR);
	write(fo,a,count);
	printf("%s %d\n",a,count);
	i = -1;
	lseek(fo,SEEK_SET,0);
	rc = read(fo,&k,1);
	while(rc != 0)
	{
		i++
		if(i == 0)
		{
		ch = (char *)malloc(char);
		*ch = k;
		mcount++;
		}
		else
		{
			for(j = 0;j < mcount;j++)
			{
				if(k != *(ch + j)
				{
					ch = (char *)realloc(ch,mcount + 1)
					*(ch + mcount) = k;
					mcount++;
				}
				else
				continue;
			}				
		}
	}
}


	



