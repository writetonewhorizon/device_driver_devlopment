#include<stdio.h> 
const int a=10;
int main()
{
	int i;
	int *ptr=&a;
	*ptr=30;
	printf("%d\n",*ptr); 
return 0;
}
