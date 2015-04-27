#include<stdio.h> 
int main()
{
	int a=10;
	int b=20;
	int c=30;
	int e=20;
	//char h='m';
	int f=50;
	int d;
	d=&a-&e;
	printf("%d %u %u %u %u %u \n",d,&a,&b,&c,&e,&f);
	return 0;
}
