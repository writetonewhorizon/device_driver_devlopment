#include<stdio.h> 
int main()
{
	int num,pos;
	printf("enter the number\n");
	scanf("%d",&num);
	printf("enter the position of bit for toogling\n");
	scanf("%d",&pos);
	printf("number after toogling is %d",num^=1<<pos);
	return 0;
}
