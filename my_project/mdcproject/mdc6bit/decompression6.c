//#include<stdio.h>
//#include<unistd.h>
//#include<fcntl.h>
#include"decomvalue.c"
int decom(int ,int ,int ,int ,int);

int decompression6()
{
	int fm,fc,fde,rc,mcount = 0,ccount = 0;
	char l;
	fm = open("/home/avtar/project1/mdcproject/masterarrayg.txt",O_RDONLY);
	fc = open("/home/avtar/project1/mdcproject/compressed_codeg.txt",O_RDONLY);
	fde = open("/home/avtar/project1/mdcproject/decompressed_datag.txt",O_WRONLY | O_TRUNC);
	rc = read(fm,&l,1);
	while(rc != 0)
	{
		mcount++;
		rc = read(fm,&l,1);
	}
	rc = read(fc,&l,1);
	while(rc != 0)
	{
		ccount++;
		rc = read(fc,&l,1);
	}
	char marray[mcount],code[ccount];
	printf("ccount and mcount is %d %d\n",ccount,mcount);
	lseek(fm,SEEK_SET,0);
	lseek(fc,SEEK_SET,0);
	read(fm,marray,mcount);
	marray[mcount] = 0;
	read(fc,code,ccount);
	code[ccount] = 0;
	printf("marray is :%s\ncode is :%d\n",marray,code[ccount]);
	decom(fm,fc,fde,ccount,mcount);
return 1;
}
