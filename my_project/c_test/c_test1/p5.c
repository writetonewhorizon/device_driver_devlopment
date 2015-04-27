#include<stdio.h> 
void foo(int a, int b,int c,int d,int e, int f,int j);
int main()
{
//	foo(1,5);
	foo(7,5,6,7,8,9,5);
}
void foo(int a,int b,int c,int d,int f,int g, int h)
{
	int j;
	int *ptr = &f;
	j=0;
	while(j<a)
	{
		printf("%d\n",*ptr);
		printf("address %p\n",ptr);
		++j;
		++ptr;
	}
}
