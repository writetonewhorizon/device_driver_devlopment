#include<stdio.h> 
int main()
{
	char array[]={'a','b','c','\n','d'};
	char *p,*str,*str1;
	p=&array[3];
	str1=array;
	printf("%d\n",++*p + ++*str1-32); 
return 0;
}
