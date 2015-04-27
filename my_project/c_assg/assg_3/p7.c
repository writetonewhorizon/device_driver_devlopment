#include<stdio.h> 
int func_to_check_setbit(int n)
{
	unsigned int count = 0;
	if(n!=0)
	{
		while(n)
		{
			n&=(n-1);
			count++;
		}
	}
	else
	return count;

}
int main()
{
	int n;
	printf("enter the number : \n");
	scanf("%d",&n);
	printf("%d\n",func_to_check_setbit(n));
}
