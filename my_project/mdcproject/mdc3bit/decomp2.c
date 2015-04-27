#include"decomp3.c"
int decom2(int fm,int fc,int fde,int m_count,int c_count,unsigned char c)
{
	lseek(fm,SEEK_SET,0);
	lseek(fc,SEEK_SET,0);
	char marr[m_count],code[c_count];
	unsigned char a,b,d,x,e;
	int j;
	read(fm,marr,m_count);
	read(fc,code,c_count);
	static int i = 1;
	if(i < c_count)
	{
		a = code[i];
		printf("%d\n",code[i]);
		b = a;
		d = a;
		e = a;
		a = a >> 7;
		a = a | c;
		for(j = 0;j < m_count ;j++)
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
		b = b << 1;
		b = b >> 5;
		for(j = 0;j < m_count ;j++)
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
		d = d << 4;
		d = d >> 5;
		for(j = 0;j < m_count ;j++)
		{
			if(d == j)
			{
				x = marr[j];
				write(fde,&x,1);
				break;
			}
			else
				continue;
		}
		e = e << 7;
		e = e >> 5;
		decom3(fm,fc,fde,m_count,c_count,e);
		i += 3;
	}
	return 1;
}
