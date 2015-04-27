#include<stdio.h> 
int imin(int , int);
int main()
{
	int evil1,evil2;
	printf("enter the pair of integer (q to quit): \n");
	while((scanf("%d %d",&evil1,&evil2))==2)
	{
		printf("the loser of %d and %d is %d \n",evil1,evil2,imin(evil1,evil2));
		printf("enter a pair of enteger (q to qut):\n"); 
	}
	printf("bye\n");
	return 0;
}
int imin(int n,int m)
{
	int min;
	if(n<m)
	min = n;
	else
	min=m;
	return min;
}
