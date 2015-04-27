#include<stdio.h> 
int main()
{
	int a=10,b=20;
	int *const c=&a;
	//c=&a;
	c=&b;
	printf("%d\n",*c); 
return 0;
}
