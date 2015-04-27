#include"compression5.c"
int compress(int ,int);
int master()
{
	int fm,fo,i,j,g = 0,count = 0,mcount = 0,rc;
	char k;
	fo = open("origional5.txt",O_RDONLY);
	fm = open("masterarray5.txt",O_WRONLY |O_TRUNC);
	rc = read(fo,&k,1);
	while(rc != 0)
	{
		count++;
		rc = read(fo,&k,1);
	}
	char org[count];
	printf("count in master() is %d\n",count);
	lseek(fo,SEEK_SET,0);
	read(fo,org,count);
	org[count] = 0;
	printf("org in master is %s\n",org);
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
		}
	}
	printf("value of mcount is %d\n",mcount);
	close(fo);
	close(fm);
	compress(count,mcount);
	return(1);
}
