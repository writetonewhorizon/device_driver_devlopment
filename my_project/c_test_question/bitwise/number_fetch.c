#include<stdio.h> 
int main()
{
	int num,tamp=0;
	printf("enter the number\n");
	scanf("%d",&num);
	printf("fetch last nibble");
	tamp=num&0xf;
	printf("%d",tamp);
return 0;
}
