#include"value.c"
char value(unsigned char,int ,int);
int decom(int fm,int fc,int fde,int ccount ,int mcount)
{
	
	unsigned char x,a,b,c,result;
	int i = 0;
	char code[ccount];
	printf("ccount and mcount is %d %d\n",ccount,mcount);
//	lseek(fm,SEEK_SET,0);
	lseek(fc,SEEK_SET,0);
//	read(fm,marray,mcount);
//	marray[mcount] = 0;
	read(fc,code,ccount);
	code[ccount] = 0;
	printf("code is :%d\n",code[ccount]);
	while(i < ccount)
	{
		x = code[i];
		a = x;
		x >>= 2;
		result = value(x,fm,mcount);
		write(fde,&result,1);

		a <<= 6;
		a >>= 2;
		x = code[++i];
//		b = x;
		c = x;
		x >>= 4;
		x = x | a;
		result = value(x,fm,mcount);
		write(fde,&result,1);

		x = code[++i];
		a = x;
		c <<= 4;
		c >>= 2;
		x >>= 6;
		x = x | c;
		result = value(x,fm,mcount);
		write(fde,&result,1);

		a <<= 2;
		a >>= 2;
		result = value(a,fm,mcount);
		write(fde,&result,1);

		i++;
	}
return 1;
}
