#include<stdio.h> 
int main()
{
	int num;
	printf("enter the number\n");
	scanf("%d",&num);
	if((num&1)==0)
		printf("number is even \n");
	else
		printf("number is odd\n"); 
return 0;
}
