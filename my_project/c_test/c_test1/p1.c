#include<stdio.h> 
int main()
{
	struct node
	{
		int a;
		int b;
		int c;
	};
	struct node s={3,4,5};
	struct node *pt=&s;
	printf("%d",*(int *)pt);
}
