#include<stdio.h>
int main()
{
	char arr[]="C Question Bank";
	char *p;
	p+=3;
	p=arr;
	p+=3;
	*p=97;
	printf("%s %s",arr,*p);
return 0;
}
