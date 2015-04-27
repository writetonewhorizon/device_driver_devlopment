#include<stdio.h>
#include<string.h>
int main()
{
	int a,b,c,d;
	char *p = ( char *)0;
	int *q = ( int *)0;
	float *r = ( float *)0;
	double *s = 0;
	a = (int)(p+1);
	b = (int)(q+1);
	c = (int)(r+1);
	d = (int)(s+1);
	printf("%d %d %d %d",a,b,c,d);
	printf("%p %p %p %p",p,q,r,s);
return 0;
}
