#include<stdio.h> 
int main()
{
	float year = 3.156*107;
	int age;
	float sec;
	printf("enter your age :");
	scanf("%d",&age);
	sec = age * year;
	printf("age in sec = %f,age =  %d,sec per year =  %f\n",sec,age,year);
	return 0;
}
