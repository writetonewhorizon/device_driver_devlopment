#include<stdio.h> 
int main()
{
	int num;
	printf("enter the number\n");
	scanf("%d",&num);
	if((num&num-1)==0)
		printf("number is power of two\n");
	else
		printf("number is not power of two\n");
	return 0;
}
