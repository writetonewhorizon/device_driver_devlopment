#include<stdio.h> 
int main()
{
	int n,i,j,temp;
	printf("enter the arrray size : ");
	scanf("%d",&n);
	int arr[n];
	printf("enter the element of the array :  ");
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	for(i=0;i<n;i++)
	{
		for(j=i;j<n;j++)
		{
			if(arr[j]>arr[i])
			{
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
	for(i=0;i<n;i++)
	{
		printf("arr[%d]=%d\n",i,arr[i]); 
	}
	return 0;
}
