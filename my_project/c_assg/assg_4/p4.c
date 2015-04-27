#include<stdio.h> 
int main()
{
	int n,rotate,i,k=0;
	printf("Enter the size of the array.\n");
	scanf("%d",&n);
	int arr[n],arr1[n];
	printf("Enter elements of the array.\n");
	for(i=0;i<n;i++)
	scanf("%d",&arr[i]);

	printf("Entered array is --> [ ");
	for(i=0;i<n;i++)
	printf("%d ",arr[i]); 
	printf("]");
	printf("\nEnter how much number of time you want to rotate the array\n");
	scanf("%d",&rotate);
	for(i=(n-rotate);i<n;i++)
	{
		arr1[k]=arr[i];
		k++;
	}
	for(i=0;i<(n-rotate);i++)
	{
		arr1[k]=arr[i];
		k++;
	}
	printf("rotated arr1 is ----> ["); 
	for(i=0;i<n;i++)
	{
		printf(" %d",arr1[i]); 
	}
	printf("]\n"); 
	return 0;
}
