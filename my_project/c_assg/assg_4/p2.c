#include<stdio.h> 
#include<string.h> 
int main()
{
	int n,i,j;
	printf("enter the no : ");
	scanf("%d",&n);
	int arr[n][n];
	for(i=0;i<=n;i++)
	{
		for(j=0;j<=i;j++)
		{
			if(j==0 || i==j)
			arr[i][j]=1;
			else
			//arr[i][j]=arr[i-1][j-1]+arr[i-1][j];
			//arr[i][j]=arr[i-1][j-1] + arr[i-1][j-1];
			arr[i][j]=i;
		printf(" %d ",arr[i][j]);
		}
		printf("\n");	
	}
return 0;
}
