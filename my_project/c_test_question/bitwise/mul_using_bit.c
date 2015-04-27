#include<stdio.h> 
int addnumber(int sum,int a)
{
	int carry=0;
	while(a!=0)
	{
		carry=(sum&a)<<1;
		sum=sum^a;
		a=carry;
	}
	return sum;

}
int main()
{
	int a,b,i,sum=0;
	printf("enter the number\n");
	scanf("%d %d",&a,&b);
	for(i=0;i<b;i++)
	{
		sum=addnumber(sum,a);
		printf("addition=%d\n",sum); 
	}
	printf("multiplication of number is %d\n",sum); 

}
