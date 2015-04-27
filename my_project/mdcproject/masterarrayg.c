//#include"compression6.c"
//int compress(int ,int,int);
#include"/home/avtar/project1/mdcproject/mdc3bit/compression3.c"
#include"/home/avtar/project1/mdcproject/mdc4bit/compression_opr.c"
#include"/home/avtar/project1/mdcproject/mdc5bit/compression5.c"
#include"/home/avtar/project1/mdcproject/mdc6bit/compression6.c"
#include"/home/avtar/project1/mdcproject/mdc7bit/compression7.c"

int  compress(int ,int);
int compress4();
int compress5(int ,int);
int compress6(int ,int,int);
int compress7(int ,int,int);


int decision(int);
int masterarr()
{
	int fm,fo,i,j,g = 0,count = 0,mcount = 0,rc,go;
	char k;
	fo = open("origionalg.txt",O_RDONLY);
	fm = open("masterarrayg.txt",O_WRONLY |O_TRUNC);
	rc = read(fo,&k,1);
	while(rc != 0)
	{
		count++;
		rc = read(fo,&k,1);
	}
	char org[count];
	printf("count in masterarr() is %d\n",count);
	lseek(fo,SEEK_SET,0);
	read(fo,org,count);
	org[count] = 0;
	printf("org in masterarr is %s\n",org);
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
//	close(fo);
	close(fm);
	go = decision(mcount);
	printf("go is = %d\n",go);
	if(go == 3)
	{
		compress(count,mcount);
		printf("3 bit compression has been completed\n");
		return 1;
	}
	if(go == 4)
	{
		compress4();
		printf("4 bit compression has been completed\n");
		return 1;
	}
	if(go == 5)
	{
		compress5(count ,mcount);
		printf("5 bit compression has been completed\n");
		return 1;
	}
	if(go == 6)
	{
		compress6(fo,count ,mcount);
		printf("6 bit compression has been completed\n");
		return 1;
	}
	if(go == 7)
	{
		compress7(fo,count,mcount);
		printf("7 bit compression has been completed\n");
		return 1;
	}
//	compress(fo,count,mcount);
}



int decision(int mcount)
{
	int go;
	if(mcount <= 8)
		return 3;
	if(mcount <= 16)
		return 4;
	if(mcount <= 32)
		return 5;
	if(mcount <= 64)
		return 6;
	if(mcount <= 128)
		return 7;
}
