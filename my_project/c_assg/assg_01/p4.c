#include<stdio.h> 
int main()
{
	double d=3.2,x;
	int i=2,y;
	x=(y=d/i)*2;
	printf("%g\t%g\n",(double)x,(double)y);
	y=(x=d/i);
	printf("%g\t%g\n",(double)(x),(double)(y));
	y=d*(x=2.5/d);
	printf("%g\t%g\n",(double)(y),(double)x);
	x=d*(y=((int)2.9+1.1/d));
	printf("%g\t%g\n",(double)(x),(double)(y));
	return 0;
}
