#include<stdio.h> 
#define TIME 60;
int main()
{
	int n=1,x,y;
	while(n)
	{
		printf("enter the number:  ");
		scanf("%d",&n);
		if(n!=0)
		{
			x=n/TIME;
			y=n%TIME;
			printf("time is %d::%d minute\n",x,y);
		}
	}
	return 0;
}
