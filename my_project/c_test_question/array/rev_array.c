#include<stdio.h> 
int main()
{
	int i;
	int array[]={1,2,3,4,5};
	int len=sizeof(array)/sizeof(int);
	printf("len=%d  , array_addraess=%p\n ",len,array);
	for(i=len-1;i>=0;i--)
		printf("%d\n",array[i]);
return 0;
}
