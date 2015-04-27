#include<stdio.h> 
int main()
{
	int *a,*s, v=10;

	a=&v;

	s=a;

	a++;

	int intsize=(int)a-(int)s;

	printf("%d\n",intsize);
}
