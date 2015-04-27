//const keyword in c doesn’t make any variable as constant but it only makes the variable as read only. With the help of pointer we can modify the const variable
#include<stdio.h>
int main()
{
	const int x=25;
	int * const p=&x;
	*p=2*x;
	printf("%d",x);
	
return 0;
}
