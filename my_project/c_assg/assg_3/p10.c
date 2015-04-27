#include<stdio.h>
#include<string.h> 
int main()
{
	int n=1;
	int i=0;
	int even_count=0,odd_count=0;
	int avE=0,avO=0;
	int arr[30];
	memset(&arr,'\0',sizeof(arr));
	while(n)
	{
		
		printf("enter the number : ");
		scanf("%d",&n);
		if(n%2==0)
		{
			
			arr[i]=n;
			avE=avE+arr[i];
			even_count++;

		}
		else
		{
			arr[i]=n;
			avO=avO+arr[i];
			odd_count++;
		}
		i++;
	}
		printf("even_count=%d\n",even_count); 
		avE=avE/even_count;
		printf("even average value =%d\n",avE); 
		printf("odd_count=%d\n",odd_count); 
		avO=avO/odd_count;
		printf("odd average value =%d\n",avO); 
	return 0;
}
