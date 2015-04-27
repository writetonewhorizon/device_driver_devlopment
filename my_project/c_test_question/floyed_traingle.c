#include<stdio.h> 
int main()
{
	int i=0,j=0,max,k=1;
	printf("enter he number\n");
	scanf("%d",&max);
	for(i=0;i<max;i++)
	{
	
		for(j=0;j<=i;j++,k++)
		{
			printf(" %d",k);
		}
	printf("\n");
	}
return 0;
}
