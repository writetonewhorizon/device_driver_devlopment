#include<stdio.h> 
int main()
{
	int num;
	int count=0;
	printf("enter the number\n");
	scanf("%d",&num);
	while(num)
	{
		if(num&1==1)
			count++;
		num=num>>1;
	}
	printf("number of ones in number is %d",count);
	return 0;
}
