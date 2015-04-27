unsigned char funx(unsigned char ,int ,int);
int compress7(int fo,int count ,int mcount)
{
	int fm,fc,i = 0;
	unsigned char a,b,c,x,value;
	char org[count],marray[mcount];
	lseek(fo,SEEK_SET,0);
	fm = open("/home/avtar/project1/mdcproject/masterarrayg.txt",O_RDONLY);
	fc = open("/home/avtar/project1/mdcproject/compressed_codeg.txt",O_WRONLY |O_TRUNC);
	read(fo,org,count);
	org[count] = 0;
	printf("org in compress is %s\n",org);
	read(fm,marray,mcount);
	marray[mcount] = 0;
	printf("marray in compress is %s\n",marray);
	for(i = 0;i < count;i++)
	{
		x = org[i];
		a = fun(x,fm,mcount);
		a <<= 1;
		x = org[++i];
		b = fun(x,fm,mcount);
		c = b;
		b >>= 6;
		value = a | b;
		write(fc,&value,1);
		printf("value is %d\n",value);
		c <<= 2;
		x = org[++i];
		x = fun(x,fm,mcount);
		a = x;
		x >>= 5;
		value = c | x;
		write(fc,&value,1);
		printf("value is %d\n",value);
		a <<= 3;
		x = org[++i];
		x = fun(x,fm,mcount);
		b = x;
		x >>= 4;
		value = a | x;
		write(fc,&value,1);
		printf("value is %d\n",value);
		b <<= 4;
		x = org[++i];
		x = fun(x,fm,mcount);
		a = x;
		x >>= 3;
		value = b | x;
		write(fc,&value,1);
		printf("value is %d\n",value);
		a <<= 5;
		x = org[++i];
		x = fun(x,fm,mcount);
		b = x;
		x >>= 2;
		value = a | x;
		write(fc,&value,1);
		printf("value is %d\n",value);
		b <<= 6;
		x = org[++i];
		x = fun(x,fm,mcount);
		c = x;
		x >>= 1;
		value = b | x;
		write(fc,&value,1);
		printf("value is %d\n",value);
		c <<= 7;
		x = org[++i];
		x = fun(x,fm,mcount);
		value = c | x;
		write(fc,&value,1);
		printf("value is %d\n",value);
		
	}
	return 1;
}
unsigned char funx(unsigned char x,int fm,int mcount)
{
	lseek(fm,SEEK_SET,0);
	unsigned char marray[mcount],z;
	read(fm,marray,mcount);
	marray[mcount] = 0;
	int j;
	for(j = 0;j < mcount;j++)
	{
		if(x == marray[j])
		{
			z = j;
			break;
		}
		else
			continue;
	}
	return z;
}
