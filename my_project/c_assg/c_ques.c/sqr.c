#include<stdio.h> 
#define SQR(b) b*b;
int main()
{
	int b=4;
	int c;
	c=SQR(++b);
	printf("%d %d\n",b,c);
	return 0;
}
