//#include"go2.c"
int go2(int ,int,int,int,int,int,unsigned char);

int go1(int fo,int fm,int fc,int f,int count,int mcount,unsigned char pass)
{
	char k[count],r[mcount];
	int l = 3 +(f*8),s = 1,q,o = 0,i,j;
	static int f1 = -1;
	unsigned char x,s_x0,s_x1,s_x2,temp,temp1,store,pass1,d;
	printf("START of go1\n");
//	printf("fo is %d\n",fo);
//	printf("fm is %d\n",fm);
//	printf("fc is %d\n",fc);
	printf("l in go1 is %d\n",l);
	lseek(fo,SEEK_SET,0);
	read(fo,&k,count);
	lseek(fm,SEEK_SET,0);
	read(fm,&r,mcount);
	d = k[l];
//	q = (11- 3) / 8;
//	printf("q in go1 is%d\n",q);
	if(d != '\0')
	{
		for(i = l;i < (l + 3);i++)
		{
			for(j = 0;j < mcount;j++)
			{
				if(k[i] == r[j])
				{
					x = j;
					break;
				}
				else
					continue;

			}
			if(j == mcount)
			{
				printf("Exit from go1\n");
				return(1);
			}
			if(i == l)
			{
				x = x << 4;
				s_x0 = x;
			}
			if(i == l+1)
			{
				x = x << 1;
				s_x1 = x;
			}
			if(i == l + 2)
			{
				pass1 = x;
				printf("pass1 in go1 is%d\n",pass1);
				x = x >> 2;
				s_x2 = x;
			}
		}
		pass = pass << 7;
		temp = pass | s_x0;
		temp1 = temp | s_x1;
		store = temp1 | s_x2;
		o++;
		f1++;
//		l += 8;
		write(fc,&store,1);
		printf("store in go1 is %d\n",store);
		go2(fo,fm,fc,f1,count,mcount,pass1);
	printf("END of go1\n");
	}
	return (1);
}
