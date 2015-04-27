//You can modify constant variable with the help of pointers. For example:

#include<stdio.h>
int main()
{
	int i=10;
	int n=120;
	//i=n;
	//printf("%d",i);
	int *ptr=&i;
	*ptr=20;
	printf("%d",i);
return 0;
}
