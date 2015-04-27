#include<stdio.h> 
int main()
{
	const int a=10;
	//a=20;
	int *ptr=&a;
	*ptr=50;
	printf("%d\n",a); 
return 0;
}
