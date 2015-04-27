#include<stdio.h> 
int main()
{
	int i=0,j=0,max;
	printf("enter the number\n");
	scanf("%d",&max);
	for(i=0;i<max;i++)
	{
		for(j=0;j<=i;j++)
			printf("*");
		printf("\n");

	}
return 0;
}
