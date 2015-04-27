#include<stdio.h> 
int main()
{
	int arr[2]={25,38};
	int (*ptr)[2]=&arr;
	int x= *ptr++;
	printf("%d %p\n",x,ptr);
	return 0;
}
