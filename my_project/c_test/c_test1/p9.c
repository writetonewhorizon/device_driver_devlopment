#include<stdio.h>
void foo(int [][3]);
int main()
{
	int a[3][3]={{1,2,3},{4,5,6},{7,8,9}};
	foo(a);
	printf("%d\n",a[2][1]); 
}
void foo(int b[][3])
{
	printf("%d\n",b); 
	++b;
	printf("%d\n",b); 
	b[1][1]=9;
}
