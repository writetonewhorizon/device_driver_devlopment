#include<stdio.h>	
int main()
{
	int num;
	int pos,pos1;
	printf("enter the number\n");
	scanf("%d",&num);
	printf("enter the position to swap bit\n");
	scanf("%d %d",&pos,&pos1);
	if(num>>pos == num >> pos1)
		printf("number is already swapped\n");
	else
		printf("swapped number is %d\n",num^(1<<(pos)|1<<(pos1)));

return 0;
}
