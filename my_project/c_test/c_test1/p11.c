#include<stdio.h> 
int main()
{
	struct 
	{
		char a[11];
		int i;
	}st={ "done" ,10};
	printf("%s\n",(&st)->a);
	printf("%d\n",(&st)->i); 

}
