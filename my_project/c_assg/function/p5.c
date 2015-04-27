#include<stdio.h>
long int rec(int );
int main()
{
	int x,y;
	printf("enter the number :\n");
	scanf("%d",&x);
	printf("factorial of %d = %ld\n",x,rec(x));
	return 0;
}
long int rec(int x)
{
	if(x==0)
	return 1;
	else
	return x * rec(x-1);
}
