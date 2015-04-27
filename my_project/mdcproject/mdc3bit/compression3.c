//#include<stdio.h>
//#include<unistd.h>
//#include<fcntl.h>
#include"go1.c"
#include"go2.c"
int go1(int ,int ,int ,int,int,int,unsigned char);
int compress(int count,int mcount)
{
	int fo,fm,fc,q;
	char k[count],r[mcount];
	fo = open("/home/avtar/project1/mdcproject/origionalg.txt",O_RDONLY);
	fm = open("/home/avtar/project1/mdcproject/masterarrayg.txt",O_RDONLY);
	fc = open("/home/avtar/project1/mdcproject/compressed_codeg.txt",O_WRONLY | O_TRUNC);
	read(fo,&k,count);
	read(fm,r,mcount);
//	q = 11/8;
//	printf("q is main is %d\n",q);
//	char k[] = {"old is golds"};
//	char r[] = {"old isg"};
	unsigned char s_x0,s_x1,s_x2,store,x,temp,pass,d;
	int i,j,l = 0,o = 0,f = -1;
	d = k[0];
	while(d != '\0')
	{
	l = 8*o;
	printf("l in main is %d\n",l);
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
		if(j == 7)
		{
			printf("EXIT from main\n");
			goto A;

		}
		if(i == l+0)
		{
			x = x << 5;
			s_x0 = x;
		}
		if(i == l+1)
		{
			x = x << 2;
			s_x1 = x;
		}
		if(i == l+2)
		{
			pass = x;
			x = x >> 1;
			s_x2 = x;
		}
		
	}
	temp = s_x0 | s_x1;
	store = temp | s_x2;
	o++;
	f++;
	l = 8*o;
	write(fc,&store,1);
	printf("store in main is %d\n",store);
//	if(o < 2)	
	go1(fo,fm,fc,f,count,mcount,pass);
	d = k[8*o];
	}
A:	return (1);

}

