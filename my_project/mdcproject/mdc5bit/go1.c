#include"fundecomp.c"
char function(unsigned char ,int ,int);

int go1(int fc,int fm,int fde ,int ccount,int mcount)
{
	char code[ccount],marray[mcount],result;
	unsigned char x,a,b,c;
	int i = 0;
	lseek(fc,SEEK_SET,0);
	lseek(fm,SEEK_SET,0);
	read(fc,code,ccount);
	code[ccount] = 0;
	printf("code[last] is %d\n",code[ccount]);
	read(fm,marray,mcount);
	code[mcount] = 0;
	//while(code[i] != 0 || i == 0)
	while(i < ccount)
	{
		x = code[i];
		a = x;
		x >>= 3;
		result = function(x,fm,mcount);
		write(fde,&result,1);
		printf("result is %c\n",result);
		a <<= 5;
		a >>= 3;
		x = code[++i];
		if(i == ccount)
			goto A;
		b = x;
		c = x;
		x >>= 6;
		x = x | a;
		result = function(x,fm,mcount);
		write(fde,&result,1);
		printf("result is %c\n",result);
		b <<= 2;
		b >>= 3;
		result = function(b,fm,mcount);
		write(fde,&result,1);
		printf("result is %c\n",result);
		c <<= 7;
		c >>= 3;
		x = code[++i];
		if(i == ccount)
			goto A;
		b = x;
		x >>= 4;
		x = x | c;
		result = function(x,fm,mcount);
		write(fde,&result,1);
		printf("result is %c\n",result);
		b <<= 4;
		b >>= 3;
		x = code[++i];
		if(i == ccount)
			goto A;
		a = x;
		c = x;
		x >>= 7;
		x = x | b;
		result = function(x,fm,mcount);
		write(fde,&result,1);
		printf("result is %c\n",result);
		a <<= 1;
		a >>= 3;
		result = function(a,fm,mcount);
		write(fde,&result,1);
		printf("result is %c\n",result);
		c <<= 6;
		c >>= 3;
		x = code[++i];
		if(i == ccount)
			goto A;
		a = x;
		x >>= 5;
		x = x | c;
		result = function(x,fm,mcount);
		write(fde,&result,1);
		printf("result is %c\n",result);
		a <<= 3;
		a >>= 3;
		result = function(a,fm,mcount);
		write(fde,&result,1);
		printf("result is %c\n",result);
		i++;
		printf("i = %d\n",i);
	}
A:	return 1;
}
