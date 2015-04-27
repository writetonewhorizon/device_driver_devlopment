#include<stdio.h> 
void main()
{
	int a=4;
	int b=5;
	int *arr1[2]={&a,&b};
	int *arr2[2]={&a,&b};
	int *( *arr[2] )[2]={&arr1,&arr2};
	printf("%d %d\t",*(*arr[0])[1],  *(*(**(arr+1)+1)));
}
