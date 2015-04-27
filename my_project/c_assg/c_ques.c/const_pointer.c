#include<stdio.h> 
int main()
{
	int x=10;
	int y=20;
	const int *ptr;
	ptr=&x;
	printf("x=%d\n",*ptr);
	*ptr=20;
	printf("x=%d",*ptr);
return 0;

}
