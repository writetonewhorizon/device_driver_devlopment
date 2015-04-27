#include<stdio.h> 
int main()
{
	int n;
	int a =15;
	int b = 5,c=6;
	int d = 18;
	printf("enter the number : ");
	scanf("%d",&n);
	if(n%a==0)
	printf("the no. is spacial\n");
	else if(n>999)
	printf("the no. is big\n");
	else if(n%b==0 && n%c==0 && n%d!=0)
	printf("the no. is weired\n");
	else if(n>999 || n%b==0 && n%c==0 && n%d !=0)
	printf("the no. is scary");
	return 0;
}
