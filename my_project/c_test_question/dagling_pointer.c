#include<stdio.h>
int *call();
int main()
{
	int *ptr;
	int ptr1;			/*wild pointer ie it is not intilized */
	ptr=call();
	printf("%d\n",ptr1);
	printf("%d",*ptr); 		// dagling pointer
return 0;
}
int * call()
{
/*A pointer which still pointing to object that has been deleted is called dangling pointer.so to avoid that condition make that variable static*/
	static int x=25; 
	//int x=25;
	++x;
	return &x;
}
