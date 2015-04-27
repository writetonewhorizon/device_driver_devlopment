#include<stdio.h> 
int main()
{
	int x=1,y=1;
	for(;y;printf("%d %d",x,y))
	{
		y=x++<=5;
	}
	return 0;
}
