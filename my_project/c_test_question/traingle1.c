#include<stdio.h> 
int main()
{

	int i=0,j=0,max;
	printf("enter the number\n");
	scanf("%d",&max);
	int k=max;
	for(i=0;i<max;i++)
	{
		for(j=0;j<i;j++)
		{
			printf(" ");
		}
		for(j=0;j<k;j++)
		{
			printf("*");
		}
		k--;
	printf("\n");
	}
	return 0;
}
