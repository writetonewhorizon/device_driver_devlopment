#include<stdio.h> 
int main()
{
	char c='d';
	double a=1.3576;
	float f=1.654;
	int aa=3.0;
	printf("%f\n",a);
	printf("%f\n",aa);
	printf("%f\n",f);
	printf("%f %p\n",aa,&aa);
	printf("%d %p\n",aa,&aa);
	printf("%c\n",c);
	printf("%d %p\n",c,&c);
	printf("%f %p\n",c,&c);
}
