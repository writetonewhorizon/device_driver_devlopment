#include<stdio.h>
#include<string.h>
int main()
{
	double a = 5.5,b = 10.5,c;
	double *p = &a,*q = &b;
	printf("%u\n",p);
	printf("%u\n",q);
	c = p - q;
	printf("%d" , c);
return 0;
}
