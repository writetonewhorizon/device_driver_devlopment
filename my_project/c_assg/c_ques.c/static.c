#include<stdio.h>
int main()
{
	int b=16;
	static int a=6;/why we cannot initilize with a=b/
	a=b;
	a++;
	printf("a=%d\n",a); 
	return 0;
}
