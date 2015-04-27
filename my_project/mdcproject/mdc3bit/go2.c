int go2(int fo,int fm,int fc,int f1,int count,int mcount,unsigned char pass1)
{
	printf("START of go2\n");
//	printf("fo in go2 is %d\n",fo);
//	printf("fm in go2 is %d\n",fm);
//	printf("fc in go2 is %d\n",fc);
	printf("pass 1 in go2 is%d\n",pass1);
	unsigned char k[count],r[mcount],store,x,s_x0,s_x1,temp,d;
	int l = 6 +(8*f1),i,j,o = 0,q;
	printf("l in go2 is %d\n",l);
	lseek(fo,0,SEEK_SET);
	read(fo,k,count);
//	printf("k[] is %s\n",k);
	lseek(fm,0,SEEK_SET);
	read(fm,&r,mcount);
//	printf("r[] is %s\n");
//	printf("Element is %c %c\n",r[5],k[5]);
	d = k[l];

//	q = (11 - 6) / 8;
	if(d != '\0')
	{
		for(i = l;i < (l + 2);i++)
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
			if(j == 7)
			{
				printf("Exit from go2\n");
				return(1);
			}
			if(i == l)
			{
				x = x << 3;
				printf("l = 6 is %d\n",x);
				s_x0 = x;
			}

			if(i == l+1)
			{
				s_x1 = x;
				printf("l = 7 is %d\n",x);
			}
		}
		pass1 = pass1 << 6;
		printf("pass1 after shift is%d\n",pass1);
		temp = pass1 | s_x0;
		store = temp | s_x1;
//		l++;
//		o++;	
		write(fc,&store,1);
		printf("store in go2 is %d\n",store);
	printf("END of go2\n");
	}
	return(1);
}
