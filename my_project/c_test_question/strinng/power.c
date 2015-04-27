#include<stdio.h> 
int main()
{
	int num;
	printf("enetr the number\n");
	scanf("%d",&num);
	if(num&(num-1)==0)
	{
		printf("the num %d is power of two\n",num);
		num=num<<1;
	}	
	else
	{
		int i=31;
		while((num&(1<<i))==0)
		{
			if(i==0)
				printf("the next number which is prwer of two is 1\n");
			
			else
			{
				i--;
			}
		}
		if(i<30)
		{
			num=1<<i+1;
			printf("the next number which is prwer of two is %d\n",num);
		}
		else
			printf("the next number which is prwer of two is overflow number ");
			
	}
	return 0;
}
