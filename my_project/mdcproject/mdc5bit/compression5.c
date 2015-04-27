#include"function.c"
unsigned char fun(unsigned char,int,int);
int compress5(int count,int mcount)
{
	int fo,fm,fc,i = 0,j = 0,s = 0;
	fo = open("/home/avtar/project1/mdcproject/origionalg.txt",O_RDONLY);
	fm = open("/home/avtar/project1/mdcproject/masterarrayg.txt",O_RDONLY);
	fc = open("/home/avtar/project1/mdcproject/compressed_codeg.txt",O_WRONLY |O_TRUNC);
	char org[count],marray[mcount];
	printf("count and mcount in compress is %d & %d resp.\n",count,mcount);
	unsigned char x,a,b,c,result,temp0,temp1;
	read(fo,org,count);
	org[count] = 0;
	read(fm,marray,mcount);
	printf("org in compress is %s\n",org);
	while(org[i] != 0)
	{
		printf("FIRST\n");
		s++;
	 	x = org[i];
		a = fun(x,fm,mcount);
		a <<= 3;
		x = org[++i];
		if(x == '\0')
			goto EXIT;
		b = fun(x,fm,mcount);
		temp0 = b;
		b >>= 2;
		result = a | b;
		write(fc,&result,1);
		printf(">>>>>>>>>>result is %u\n",result);
		printf("SECOUND\n");
		s++;
		x = org[++i];
		if(x == '\0')
			goto EXIT;
		temp0 <<= 6;
		b = fun(x,fm,mcount);
		b <<= 1;
		x = org[++i];
		if(x == '\0')
			goto EXIT;
		c = fun(x,fm,mcount);
		temp1 = c;
		c >>= 4;
		b = b |temp0;
		result = c | b;
		write(fc,&result,1);
		printf(">>>>>>>>>>result is %u\n",result);
		printf("THIRD\n");
		s++;
		temp1 <<= 4;
		x = org[++i];
		if(x == '\0')
			goto EXIT;
		b = fun(x,fm,mcount);
		temp0 = b;
		b >>= 1;
		result = temp1 | b;
		write(fc,&result,1);
		printf(">>>>>>>>>>result is %u\n",result);
		printf("FOURTH\n");
		s++;
		temp0 <<= 7;
		x = org[++i];
		if(x == '\0')
			goto EXIT;
		b = fun(x,fm,mcount);
		b <<= 2;
		x = org[++i];
		if(x == '\0')
			goto EXIT;
		c = fun(x,fm,mcount);
		temp1 = c;
		c >>= 3;
		b = b | temp0;
		result = b | c;
		write(fc,&result,1);
		printf(">>>>>>>>>>result is %u\n",result);
		printf("FIFTH\n");
		s++;
		temp1 <<= 5;
		x = org[++i];
		if(x == '\0')
			goto EXIT;
		c = fun(x,fm,mcount);
		result = temp1 | c;
		write(fc,&result,1);
		printf(">>>>>>>>>>>result is %u\n",result);
		i++;
	}
	printf("no. of bytes are %dbytes\n",s);
	return 1;
EXIT:	x = org[i - 1];
	result = fun(x,fm,mcount);
	write(fc,&result,1);
	s++;
	printf("EXIT result is %c\n",x);
	printf("no. of bytes are %dbytes\n",s);
	return 1;
}
