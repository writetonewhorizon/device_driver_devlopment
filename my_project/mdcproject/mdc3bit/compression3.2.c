#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include"go1.c"
#include"go2.c"
int go1(int ,int ,int ,char);
int main()
{
	int fo,fm,fc,q;
	char k[11],r[7];
	fo = open("origional.txt",O_RDONLY);
	fm = open("masterarray3.txt",O_RDONLY);
	fc = open("compressed_code3.txt",O_WRONLY);
	read(fo,&k,11);
	read(fm,r,7);
	q = 11/8;
	printf("q is main is %d\n",q);
	
//	char k[] = {"old is golds"};
//	char r[] = {"old isg"};
	char s_x0,s_x1,s_x2,store,x,temp,pass;
	int i,j,l = 0,o = 0;

	while(l%8 == 0 && o <= q)
	{
	for(i = l;i < (l + 3);i++)
	{
		for(j = 0;j < 7;j++)
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
			printf("EXIT\n");
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
	l = 8*o;
	write(fc,&store,1);
	printf("store in main is %d\n",store);
	if(o < 2)	
	go1(fo,fm,fc,pass);
	d = k[8*o];
	}
A:	return 0;

}

