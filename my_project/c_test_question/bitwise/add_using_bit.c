#include<stdio.h> 
int main()
{
	int a=0,b=0,carry=0;
	printf("enter the number\n"); 
	scanf("%d %d",&a,&b);
	while(b!=0)
	{
		carry=(a&b)<<1;
		a=a^b;
		b=carry;
	}
	printf("addition of a+b=%d\n",a);
	return 0;
}
