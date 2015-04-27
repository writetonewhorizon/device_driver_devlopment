//#include<stdio.h>
//#include<unistd.h>
//#include<fcntl.h>
#include"go1.c"
int go1(int ,int ,int ,int ,int);

int decompression5()
{
	int fc,fm,fde,i,ccount = 0,mcount = 0,rc;
	char k;
	fm = open("/home/avtar/project1/mdcproject/masterarrayg.txt",O_RDONLY);
	fc = open("/home/avtar/project1/mdcproject/compressed_codeg.txt",O_RDONLY);
	fde = open("/home/avtar/project1/mdcproject/decompressed_datag.txt",O_WRONLY | O_TRUNC);
	rc = read(fc,&k,1);
	while(rc != 0)
	{
		ccount++;
		rc = read(fc,&k,1);
	}
	rc = read(fm,&k,1);
	while(rc != 0)
	{
		mcount++;
		rc = read(fm,&k,1);
	}
	printf("ccount is %d\nmcount is %d\n",ccount ,mcount);
	unsigned char marray[mcount],code[ccount];
	lseek(fm,SEEK_SET,0);
	lseek(fc,SEEK_SET,0);
	read(fm,marray,mcount);
	marray[mcount] = 0;
	read(fc,code,ccount);
	code[ccount] = 0; 
	printf("masterarray is %s\ncode[last] is %d\n",marray,code[ccount]);
	go1(fc,fm,fde,ccount,mcount);
	return 1;
}
