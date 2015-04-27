#include<stdio.h> 
int main()
{
	int a=5;
	int b=5;
	a=a<<3; 		/* a*a^3*/
	b=b>>3;			/*a/a^3*/
	printf("a=%d,b=%d\n",a,b);
return 0;
}
