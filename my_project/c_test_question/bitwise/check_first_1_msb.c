#include<stdio.h> 
int func(int num)
{
	int position;
	while(num)
	{
		if(num&(1<<31)==1)
		{
			printf("position is %d",position);
			break;
		}
		else
		{
			num=num<<1;
			position++;
		}

	}
	return 32-position;
}
int main()
{
	int num,pos;
	printf("enter the number\n");
	scanf("%d",&num);
	pos=func(num);
	printf("position of first msb binary number 1 is %d",pos);
return 0;
}
