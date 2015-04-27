#include<stdio.h>
#include<limits.h> 
int main()
{
	int a,b;
	long int result;
	printf("enter the number to multiply : \n");
	scanf("%d\n %d",&a,&b);
	result = a*b;
	printf("%d\n",INT_MAX);
	if(result>0)
	{
	printf("a=%d,b=%d,result = %d\n",a,b,result); 
	return 0;
	}
	else
	{
	printf("result is not in range\n");
	return -1;
	}
return 0;
}
