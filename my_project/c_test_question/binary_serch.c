#include<stdio.h> 
#include<string.h> 
int main()
{
	int array[10],i,lb,ub,mid,num,flag=0;
	printf("enter the sorted element in the array\n"); 
	for(i=0;i<10;i++)
	{
		scanf("%d",&array[i]);
	}
	printf("enter  the number\n"); 
	scanf("%d",&num);
	lb=0;
	ub=sizeof(array)/4-1;
	printf("sizeof array =%d\n",ub); 
	while(lb<=ub)
	{
		mid=(lb+ub)/2;
		if(num==array[mid])
		{
			flag=1;
			break;
		}
		else if(num<array[mid])
			ub=mid-1;
		else
			lb=mid+1;
	}
	if(flag==0)
		printf("elemant is not found\n");
	else 
		printf("number is found\n"); 
	
	return 0;
}
