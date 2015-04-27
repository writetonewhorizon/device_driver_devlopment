#include<stdio.h> 
int main()
{
	int a=15;
	int b=20;
	int tamp=0;
	tamp = a;
	a=b;
	b=tamp;
	printf("tamp = %d, a=%d,b =%d\n",tamp,a,b); 

}
