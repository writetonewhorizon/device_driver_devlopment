#include<stdio.h> 
int main()
{
	int i;
	int arr[10]={10,20,30,40,50,60,70,1,2,3};
	char *ptr;
	//int *ptr;
	ptr=(char *)arr;
	for(i=0;i<10;i++)
	{
	printf("%d\n",*ptr);
	ptr+=4;
	}
}
