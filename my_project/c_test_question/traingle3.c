#include<stdio.h> 
int main()
{
	int i,j,max,l=1;
	printf("enter the number\n");
	scanf("%d",&max);
	int k=max-1;
	for(i=0;i<max;i++)
	{
		for(j=0;j<k;j++)
			printf("  "); 
		for(j=0;j<l;j++)
			printf(" *");
		k--;
		l=l+2;
		printf("\n"); 
	}
return 0;
}
