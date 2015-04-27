//#include<stdio.h>
//#include<unistd.h>
//#include<fcntl.h>
#include"decomp1.c"
int decom1(int,int,int,int);

decompression3()
{
	int fm,fc,c_count = -1,m_count = -1,rc = 1,i;
	fm = open("/home/avtar/project1/mdcproject/masterarrayg.txt",O_RDONLY);
	fc = open("/home/avtar/project1/mdcproject/compressed_codeg.txt",O_RDONLY);
	char d;
	while(rc != 0)
	{
		rc = read(fm,&d,1);
		m_count++;
	}
	char marr[m_count];
	lseek(fm,SEEK_SET,0);
	read(fm,marr,m_count);
	marr[m_count] = 0;
	rc = 1;
	while(rc != 0)
	{
		rc=read(fc,&d,1);
		c_count++;
	}
	char code[c_count];
	lseek(fc,SEEK_SET,0);
	read(fc,code,c_count);
	code[c_count] = 0;
	printf("c_count is %d\n",c_count);
	for(i = 0;i < c_count;i++)
	printf("code is %d\n",code[i]);
	decom1(fm,fc,m_count,c_count);
	return 1;
}
