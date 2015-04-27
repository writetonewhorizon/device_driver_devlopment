//#include<stdio.h>
//#include<unistd.h>
//#include<fcntl.h>
int decompression4()
{
	int fde,fe,fo,d,k,m,n,rc;
	unsigned char h,c_count = 0,e_count = 0,r,x,y,z,tem;
	fde = open("/home/avtar/project1/mdcproject/compressed_codeg.txt",O_RDONLY);
	fe = open("/home/avtar/project1/mdcproject/masterarrayg.txt",O_RDONLY);
	fo = open("/home/avtar/project1/mdcproject/decompressed_datag.txt",O_WRONLY | O_TRUNC);
	rc = read(fde,&h,1);
	while(rc != 0)
	{
		c_count++;
		rc = read(fde,&h,1);
	}
	unsigned char code[c_count];
	rc = read(fe,&h,1);
	while(rc  != 0)
	{
		e_count++;
		rc = read(fe,&h,1);
	}
	printf("in decompression c_count is %d\t e_count is %d\n",c_count,e_count);
	char ekey[e_count];
	lseek(fde,SEEK_SET,0);
	read(fde,code,c_count);
	code[c_count] = 0;
	lseek(fe,SEEK_SET,0);
	read(fe,ekey,e_count);
	ekey[e_count] = 0;
//	printf("%d\n",code[13]);
//	for(i = 0;i < 20;i++)
//	printf("%c %c\n",code[i],ekey[i]);
	for(d = 0;d < c_count;d++)
	{
//		printf("%d\n",code[d]);
		x = code[d];
		z = code[d];
//		if(x >= 128)
//		{
//			y = x >> 4;
//			y = y & 0x0f;
//			printf(">128 y is %d\t",y);
//			z = z & 15;
//			printf("z is %d\n",z);
//		}		
//		if(x < 128)
//		{
		y = x >> 4;
		
//		printf("y is %d\t",y);
//		tem = z << 4;
//		z = tem >> 4;
		z = z & 15;
//		printf("z is %d\n",z);
//		}
		m = n = 0;
		if(m == 0)
		{
		for(k = 0;k < e_count;k++)
		{
			if(y == k )
			{
				r = ekey[k];
				write(fo,&r,1);
				n = 1;
				break;
			}
		}
		}
		if(n == 1);
		{
		for(k = 0;k < e_count;k++)
		{
			if(z == k )
			{
				r = ekey[k];
				write(fo,&r,1);
				break;
			}
		}
		}
	}
	return 1;
}
