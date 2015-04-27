#include<stdio.h>
int main()
{
	const volatile int a=10;
	int *ptr=&a;
	*ptr=50;
	printf("%d",a);
return 0;
}
