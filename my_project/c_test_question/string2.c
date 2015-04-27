#include<stdio.h> 
int main()
{

	char *ptr=(char *)0;
	char *ptr1=0;
	printf("%p\n",ptr);
	strcpy(ptr,"dharmender");
	printf("%s\n",*ptr);
	return 0;
}
