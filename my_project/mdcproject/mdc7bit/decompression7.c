//#include<stdio.h>
//#include<unistd.h>
//#include<fcntl.h>
#include"decompfun.c"
int fund(int ,int ,int ,int ,int);
int decompression7()

{
	int fc,fm,fde,o,ccount = 0,mcount = 0;
	char h;
	fc = open("/home/avtar/project1/mdcproject/compressed_codeg.txt",O_RDONLY);
	fm = open("/home/avtar/project1/mdcproject/masterarrayg.txt",O_RDONLY);
	fde = open("/home/avtar/project1/mdcproject/decompressed_datag.txt",O_WRONLY |O_TRUNC);
	o = read(fc,&h,1);
	while(o != 0)
	{
		ccount++;
		o = read(fc,&h,1);
	}
	char code[ccount];
	lseek(fc,SEEK_SET,0);
	read(fc,code,ccount);
	code[ccount] = 0;
	o = read(fm,&h,1);
	while(o != 0)
	{
		mcount++;
		o = read(fm,&h,1);
	}
	char marray[mcount];
	lseek(fm,SEEK_SET,0);
	read(fm,marray,mcount);
	marray[mcount] = 0;
	printf("code is %d\nmarray is %d\n",ccount,mcount);
	fund(fc,fm,fde,ccount,mcount);
	return 1;
}
