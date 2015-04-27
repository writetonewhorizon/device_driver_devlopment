#include<stdio.h> 
#define var 3
int main()
{
	char *arr[var+~0]={"dharmender","sharma"};
	char *ptr=arr[1+~0];
	printf("%c\n",*++ptr);
	return 0;
}
