#include<stdio.h> 
int main()
{
	volatile int a=15;
	printf("a=%p %d\n",&a,a);
	a++;
	int b=16;
	printf("b=%p %d\n",&b,b);
	b++;
	printf("a=%p %d\n",&a,a);
	printf("b=%p %d\n",&b,b);
	return 0;
}
