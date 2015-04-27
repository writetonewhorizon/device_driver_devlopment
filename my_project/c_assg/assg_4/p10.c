#include<stdio.h> 
int main()
{
	int i,j,k,n,temp,num,index;
	printf("enter the size of array : ");
	scanf("%d",&n);
	printf("enter the elemet you want to insert: \n"); 
	scanf("%d",&num);
	printf("enter the index number :\n");
	scanf("%d",&index);
	printf("enter the element of the array : \n");
	int arr[n];
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	for(i=0;i<n;i++)
	{
		if(i==index)
		{
			for(j=0;j<n-index;j++)
			{
				arr[n-j]=arr[n-1-j];
				printf("arr[%d]=%d\n",n-j,arr[n-1-j]); 
			}
			arr[j]=num;
		}
	}
	for(i=0;i<n;i++)
	{
		printf("arr[%d]=%d\n",i,arr[i]); 
	}
return 0;
}
