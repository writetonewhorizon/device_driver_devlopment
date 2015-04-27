#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include"/home/avtar/project1/mdcproject/mdc3bit/decompression3.c"
#include"/home/avtar/project1/mdcproject/mdc4bit/decompression4.c"
#include"/home/avtar/project1/mdcproject/mdc5bit/decompression5.c"
#include"/home/avtar/project1/mdcproject/mdc6bit/decompression6.c"
#include"/home/avtar/project1/mdcproject/mdc7bit/decompression7.c"
int decompression3();
int decompression4();
int decompression5();
int decompression6();
int decompression7();

int main()
{
	int fo,fc,rc, ocount = 0,ccount = 0;
	float o = 0,c = 0;
	char k;
	float ratio;
	fo = open("origionalg.txt",O_RDONLY);
	fc = open("compressed_codeg.txt",O_RDONLY);
	rc = read(fo,&k,1);
	while(rc != 0)
	{
		ocount++;
		o++;
		rc = read(fo,&k,1);
	}
	printf("size of origional file is %d Bytes\n",ocount);
	rc = read(fc,&k,1);
	while(rc != 0)
	{
		ccount++;
		c++;
		rc = read(fc,&k,1);
	}
	printf("size of compressed file is %d Bytes\n",ccount);
	ratio = o / c;
	printf("ratio is %f\n",ratio);
	if(ratio <= (float)8 / 3 && ratio > (float)4 / 2)
	{
		printf("Enter in 3 bit compression\n");
		decompression3();
		printf("decompression of 3 bit has been completed\n");
		return 0;
	}
	else if(ratio <= (float)4 / 2 && ratio > (float)13 / 8)
	{
		printf("Enter in 4 bit compression\n");
		decompression4();
		printf("decompression of 4 bit has been completed\n");
		return 0;
	}
	else if(ratio <= (float)13 / 8 && ratio > (float)4 / 3)
	{
		printf("Enter in 5 bit compression\n");
		decompression5();
		printf("decompression of 5 bit has been completed\n");
		return 0;
	}
	else if(ratio <= (float)4 / 3 && ratio > (float)8 / 7)
	{
		printf("Enter in 6 bit compression\n");
		decompression6();
		printf("decompression of 6 bit has been completed\n");
		return 0;
	}
	else if(ratio <= (float)8 / 7)
	{
		printf("Enter in 7 bit compression\n");
		decompression7();
		printf("decompression of 7 bit has been completed\n");
		return 0;
	}
	else
	{
		perror("decompression failed !!!");
		return 0;
	}
}
