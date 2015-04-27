#include<stdio.h> 
int main()
{
	int num;
	int position;
	printf("enter the number \n");
	scanf("%d",&num);
	printf("enter the bit position you want to reset\n");
	scanf("%d",&position);
	num &=~(1 << position);
	printf("number after bit reseting is %d\n",num);
return 0;
}
