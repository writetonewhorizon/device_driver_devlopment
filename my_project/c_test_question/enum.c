#include<stdio.h>
int main()
{
	const enum
	{
		x,
		y=20,
		z
	}p=10;
	int a=x;
	int b=y;
	int c=z;
	printf("x=%d,y=%d,z=%d,p=%d\n",x,y,z,p);
	printf("a=%d,b=%d,c=%d,p=%d\n",a,b,c,p);
	return 0;
}
