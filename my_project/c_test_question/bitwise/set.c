#include<stdio.h> 
int main()
{
	int num;
	int position;
	printf("enter the number \n");
	scanf("%d",&num);
	printf("enter the position numberyou want to set\n");
	scanf("%d",&position);
	num|=(1<<position);
	printf("%d\n",num);

}
