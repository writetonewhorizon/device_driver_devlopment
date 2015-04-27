#include<stdio.h> 
const int a;
int main()
{
	int *ptr=&a;
	ptr=20;
	printf("%d\n",*ptr);
	return 0;
}
