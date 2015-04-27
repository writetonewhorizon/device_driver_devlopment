#include<stdio.h> 
int main()
{
	int n,i,first=0,second=1,next=0;
	printf("enter the number : \n");
	scanf("%d",&n);
	for(i=0;i<=n;i++)
	{
		if(i<=1)
		next =i;
		else
		{
			next =first + second;
			first = second;
			second = next;
		}
		printf("%d\n",next);
	}
	return 0;
}
