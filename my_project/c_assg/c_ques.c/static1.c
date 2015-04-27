#include<stdio.h> 
int main()
{
	int i=0,sum=0;
	for(i=0;i<5;i++)
	{
		static int i=10;
		sum += i++;
	}
	printf("sum = %d\n",sum);
	return 0;
}
