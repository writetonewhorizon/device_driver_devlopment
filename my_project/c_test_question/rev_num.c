#include<stdio.h>
int main()
{
	int num,reverse=0;
	printf("enter the number\n");
	scanf("%d",&num);
	while(num!=0)
	{
		reverse=reverse*10 + (num%10);
		num=num/10;
	}
	printf("%d\n",reverse);
	return 0;
}
