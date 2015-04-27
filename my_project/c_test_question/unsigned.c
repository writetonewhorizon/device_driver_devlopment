#include<stdio.h>
int main()
{
	unsigned char x=-20;
	x=x&~(1<<7);
	printf("%d",x);
}
