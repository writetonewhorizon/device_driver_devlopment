#include<stdio.h> 
int main()
{
	int n,i,k,j,temp=0,count=0,comman=0,inter=0;
int arr[10]={'\0'};
	int arr1[10]={'\0'};
	int arr2[20]={'\0'};
	int arr3[30]={'\0'};
	int arr4[30]={'\0'};
	printf("enter the noumber of element of the first array : \n");
	scanf("%d",&n);
	printf("enter the  element in  the first array : \n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	for(i=0;i<n;i++)
	{
		printf("arr[%d]=%d\n",i,arr[i]); 
	}
	printf("enter the noumber of element of the  2nd array : \n");
	scanf("%d",&n);
	printf("enter the  element in  the 2nd array : \n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr1[i]);
	}
	for(i=0;i<n;i++)
	{
		printf("arr1[%d]=%d\n",i,arr1[i]); 
	}
	printf("\n"); 
	//now merg arr into third array
	for(i=0;i<n;i++)
	{
		arr2[k]=arr[i];
		k++;
	}
	for(i=0;i<n;i++)
	{
		printf("arr2[%d]=%d\n",i,arr2[i]); 
	}
	//merg 2nd array into third array
	for(i=0;i<n;i++)
	{
		arr2[k]=arr1[i];
		k++;
	}
	arr2[k]='\0'; 
	printf("\n");  
	for(i=0;i<=k;i++)
	{
		printf("arr2[%d]=%d\n",i,arr2[i]); 
	}
	printf("k=%d\n",k);	
	//now short the 3rd array
	for(i=1;i<k;i++)
	{
		for(j=1;arr2[j]!='\0';j++)
		{
			if(arr2[j-1]<arr2[j])
			{
			temp=arr2[j-1];
			arr2[j-1]=arr2[j];
			arr2[j]=temp;
			count++;
			}
		}
		
	}
		printf("count = %d\n",count); 
		for(i=0;i<=k;i++)
		{
			printf("arr2[%d]=%d\n",i,arr2[i]); 
		}

	for(i=0;i<k;i++)
	{
		if(arr2[i]!=arr2[i+1])
		{
		arr3[comman]=arr2[i];
		comman++;
		}
	}
		for(i=0;i<comman;i++)
		{
			printf("arr3[%d]=%dand union =%d\n",i,arr3[i],comman); 
		}
	for(i=0;i<k;i++)
	{
		if(arr2[i]==arr2[i+1])
		{
		arr4[inter]=arr2[i];
		inter++;
		}
	}
		for(i=0;i<inter;i++)
		{
			printf("arr4[%d]=%dand intersection =%d\n",i,arr4[i],inter); 
		}
return 0;
}
