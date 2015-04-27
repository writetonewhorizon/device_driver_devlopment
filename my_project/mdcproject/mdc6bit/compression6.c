#include"indexfun.c"
unsigned char indx(unsigned char ,int ,int);
compress6(int fo,int count,int mcount)
{
	int i = 0,fm,fc,size = 0;
	unsigned char x,a,b,c,store;
	lseek(fo,SEEK_SET,0);
	fm = open("/home/avtar/project1/mdcproject/masterarrayg.txt",O_RDONLY);
	fc = open("/home/avtar/project1/mdcproject/compressed_codeg.txt",O_WRONLY | O_TRUNC);
	char org[count],marray[mcount];
	read(fo,org,count);
	org[count] = 0;
	read(fm,marray,mcount);
	marray[mcount] = 0;
	printf("org in compress is %s\nmarray in compress is %s\n",org,marray);
	while(org[i] != 0)
	{
		x = org[i];
		a = indx(x,fm,mcount);
		a <<= 2;
		x = org[++i];
		b = indx(x,fm,mcount);
		c = b;
		b >>= 4;
		store = a | b;
		write(fc,&store,1);
		size++;
		printf("store is %d\n",store);

		c <<= 4;
		x = org[++i];
		a = indx(x,fm,mcount);
		b = a;
		a = a >>= 2;
		store = a | c;
		write(fc,&store,1);
		size++;
		printf("store is %d\n",store);

		b <<= 6;
		x = org[++i];
		a = indx(x,fm,mcount);
		store = a | b;
		write(fc,&store,1);
		size++;
		printf("store is %d\n",store);

		i++;


	}
	printf("SUCCESFULLY COMPRESSED\nsize of the compressed file is %dbytes\n",size);
	return 1;

}
