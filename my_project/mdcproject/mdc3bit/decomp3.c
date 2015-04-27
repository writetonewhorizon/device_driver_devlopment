int decom3(int fm,int fc,int fde,int m_count,int c_count,unsigned char e)
{
	lseek(fm,SEEK_SET,0);
	lseek(fc,SEEK_SET,0);
	unsigned char marr[m_count],code[c_count];
	unsigned char a,b,c,d,x;
	int j;
	read(fm,marr,m_count);
	read(fc,code,c_count);
	static int i = 2;
	if(i < c_count)
	{
		a = code[i];
		printf("%d\n",code[i]);
		b = a;
		c = a;
		d = a;
		a = a >> 6;
		a = a | e;
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
		b = b << 2;
		b = b >> 5;
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
		c = c << 5;
		c = c >> 5;
		for(j = 0;j < m_count;j++)
		{
			if(c == j)
			{
				x = marr[j];
				write(fde,&x,1);
				break;
			}
			else
				continue;
		}
	i += 3;
	}
return 1;

}
