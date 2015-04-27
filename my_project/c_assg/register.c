#include<stdio.h> 
int main()
{
	register int i=0;
	for(i=0;i<10;i++)
	{
		printf("i=%d\n",i);
	//	printf("i=%p\n",&i);
	}
	return 0;
}
