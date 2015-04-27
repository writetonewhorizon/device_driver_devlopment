#include<stdio.h> 
int main()
{
	int a,b,c,d;
	a=3;
	b=5;
	c=a,b;
	d=(a,b);
	printf("c=%d\n",c);
	printf("d=%d\n",d); 
}
