#include<stdio.h>
int main()
{
	int n;
	printf("enter the no :  ");
	scanf("%d",&n);
	if((n&n-1)== 0)
	printf("the no %d is power of 2's",n);
	else
	printf("the no %d is not power of 2's",n);
return 0;
}
