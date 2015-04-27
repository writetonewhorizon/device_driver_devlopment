#include<stdio.h> 
int main()
{
	int count=0,n;
	printf("enter the num\n");
	scanf("%d",&n);
	while(n)
	{
		if(n&1==1)
			count++;
		n=n>>1;
	}
	printf("%d\n",count);
return 0;
}
