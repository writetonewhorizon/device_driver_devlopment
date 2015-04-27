#include<stdio.h>
unsigned long int (* avg())[3]
{
	static unsigned long int arr[3] = {1,2,3};
	return &arr;
}
int main()
{
	unsigned long int (*ptr)[3];
	ptr = avg();
	printf("%d" , *(*ptr+2));
return 0;
}
