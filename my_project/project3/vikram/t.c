#include<stdio.h>
int main()
{
	int i=10;
	int x,*p = &i;
	int *q,*r;

	printf("P1:%p",p);

	q=p+5;
	r=p+2;
	x=q-r;

	printf("x:%d",x);
}
