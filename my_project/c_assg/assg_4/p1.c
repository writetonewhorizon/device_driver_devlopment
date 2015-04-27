#include<stdio.h> 
int main()
{
	int size,i;
	int even=0,odd=0;
	int arr[30];
	printf("enter the size of an array : \n");
	scanf("%d",&size);
	printf("enter the element in the  array : \n");
	for(i=0;i<size;i++)
	{
		scanf("%d",&arr[i]);
		printf("\n"); 
	}
	printf("the elemment in the array arr :\n");
	for(i=0;i<size;i++)
	{
		printf("the element in the arr[%d]= %d\n",i,arr[i]);
		if(arr[i]%2 == 0)
		{
			printf("the number arr[%d]== %d is even\n",i,arr[i]);
			even++;
		}
		else
		{
		printf("the no arr[%d]=%d is odd\n",i,arr[i]);
		odd++;
		}
	}
	printf("total even no. = %d\n",even); 
	printf("total odd no. = %d\n",odd); 

return 0;

}
