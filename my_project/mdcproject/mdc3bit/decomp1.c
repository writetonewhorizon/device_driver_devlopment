#include"decomp2.c"

int decom2(int ,int ,int ,int,int,unsigned char);
int decom1(int fm,int fc,int m_count,int c_count)
{
//	printf("org is %s\n",org);
//	printf("marr is %s\n",marr);
//	printf("code is %s\n",code);
	unsigned char x,a,b,c,d;
	int i = 0,fde,j;
//	m_count--;
//	c_count--;
	printf("m_count is  %d\n",m_count);
	printf("c_count is %d\n",c_count);
	char marr[m_count],code[c_count];
	lseek(fm,SEEK_SET,0);
	lseek(fc,SEEK_SET,0);
	read(fm,marr,m_count);
	read(fc,code,c_count);
//	printf("code 0 is %d\n",code[0]);
	fde = open("/home/avtar/project1/mdcproject/decompressed_datag.txt",O_WRONLY | O_TRUNC);
	while(i < c_count)
	{
	a = code[i];
	printf("%d\n",code[i]);
	b = a;
	c = a;
	a = a>>5;
//	printf("%d\n",a);
	for(j = 0;j < m_count;j++)
	{
		if(a == j)
		{
			x = marr[j];
			write(fde,&x,1);
			break;
		}
		else
			continue;
	}
	b = b << 3;
	b = b >> 5;
//	printf("%d\n",b);
	for(j = 0;j < m_count;j++)
	{
		if(b == j)
		{
			x = marr[j];
			write(fde,&x,1);
			break;
		}
		else
			continue;
	}
	c = c << 6;
	c = c >> 5;
	decom2(fm,fc,fde,m_count,c_count,c);
	i += 3;
	}
return 1;
}
