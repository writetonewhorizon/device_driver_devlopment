#include<stdio.h>

int main()
{
	int i,j,count,arr[10];
	printf("Enter 9 digits between 1 to 10 randomly & I will tell you the missing digit\n");
	for(i=0;i<9;i++)
	scanf("%d",&arr[i]);
	for(j=1;j<=10;j++)
	{	
		count=0;
		for(i=0;i<10;i++)
		{
			if(j==arr[i])
			break;	
			else
			count++;
		}
			if(count==10)									
			{
														
			printf("Missing Number is %d\n",j);
			break;
			}
	}

return 0;
}
