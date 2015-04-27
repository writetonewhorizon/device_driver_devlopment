//#include"extract.c"
unsigned char extract(unsigned char,int,int);
int fund(int fc,int fm,int fde,int ccount,int mcount)
{
	lseek(fc,SEEK_SET,0);
	lseek(fm,SEEK_SET,0);
	char code[ccount],marray[mcount];
	unsigned char store,x,a,b,c;
	int i,size = 0;
	read(fc,code,ccount);
	printf("ccount is %d\nmcount is %d\n",ccount,mcount);
	code[ccount] = 0;
	read(fm,marray,mcount);
	marray[mcount] = 0;
	for(i = 0;i < ccount;i++)
	{
		x = code[i];
		a = x;
		x >>= 1;
		printf("x = %d\t",x);
		store = extract(x,fm,mcount);
		printf("store is %u\n",store);
		write(fde,&store,1);
		a <<= 7;
		a >>= 1;
		x = code[++i];
		b = x;
		x >>= 2;
		x = x | a;
		printf("x = %d\t",x);
		store = extract(x,fm,mcount);
		printf("store is %u\n",store);
		write(fde,&store,1);
		b <<= 6;
		b >>= 1;
		x = code[++i];
		a = x;
		x >>= 3;
		x = x | b;
		printf("x = %d\t",x);
		store = extract(x,fm,mcount);
		printf("store is %u\n",store);
		write(fde,&store,1);
		a <<= 5;
		a >>= 1;
		x = code[++i];
		b = x;
		x >>= 4;
		x = x | a;
		printf("x = %d\t",x);
		store = extract(x,fm,mcount);
		printf("store is %u\n",store);
		write(fde,&store,1);
		b <<= 4;
		b >>= 1;
		x = code[++i];
		c = x;
		x >>= 5;
		x = x | b;
		printf("x = %d\t",x);
		store = extract(x,fm,mcount);
		printf("store is %u\n",store);
		write(fde,&store,1);
		c <<= 3;
		c >>= 1;
		x = code[++i];
		b = x;
		x >>= 6;
		x = x | c;
		printf("x = %d\t",x);
		store = extract(x,fm,mcount);
		printf("store is %u\n",store);
		write(fde,&store,1);
		b <<= 2;
		b >>= 1;
		x = code[++i];
		c = x;
		x >>= 7;
		x = x | b;
		printf("x = %d\t",x);
		store = extract(x,fm,mcount);
		printf("store is %u\n",store);
		write(fde,&store,1);
		c <<= 1;
		c >>= 1;
		x = c;
		printf("x = %d\t",x);
		store = extract(x,fm,mcount);
		printf("store is %u\n",store);
		write(fde,&store,1);
		size++;
	}
	printf("SIZE of decompressed file is %d\n",8*size);
	return 1;
}
unsigned char extract(unsigned char x,int fm,int mcount)
{
	unsigned char marray[mcount],ret;
	int j;
	lseek(fm,SEEK_SET,0);
	read(fm,marray,mcount);
	marray[mcount] = 0;
	for(j = 0;j < mcount;j++)
	{
		if(x == j)
		{
			ret = marray[j];
			break;
		}
		else
			continue;
	}
	return ret;
}
