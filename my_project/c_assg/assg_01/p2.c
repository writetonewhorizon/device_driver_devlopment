#include<stdio.h>
int main()
{
	int x,y,z;
	x=03;y=02;z=01;
	printf("%d\n",x|y&z);
	printf("%d %d %d\n",x,y,z); 
	printf("%d\n",x|y&~z);
	printf("%d\n",x^y&z);
	printf("%d\n",x&y&&z);
	x=1;y=-1;
	printf("%d\n",!x|x);
	printf("%d\n",~x|x);
	printf("%d\n",x^x);
	x<<=3;
	printf("%d\n",x);
	x>>=3;
	printf("%d\n",x); 
	y<<=3;
	//printf("%d\n",y);
	//y<<=3;
	printf("%d\n",y); 
	y>>=3;
	printf("%d\n",y);
	x=1;y=1;z=1;
	x+=y+=z;
	printf("%d\n",x<y?y:x);
	printf("%d\n",x<y?x++:y++);
	printf("%d\n",x);
	printf("%d\n",y);
	printf("%d\n",z+=x<y?x++:y++);
	printf("%d\n",y);
	printf("%d\n",x);
	x=3,y=z=4;
	printf("%d\n",z>=y>=x?1:0);
	printf("%d\n",z>=y&&y>=x);
	return 0;
}
