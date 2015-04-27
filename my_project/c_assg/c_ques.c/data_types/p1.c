
#include<stdio.h>
int main()
{
	static i=10;
	printf("%d\t",sizeof(6.5));	//bydefault the datatype of numeric const is double
	printf("%d\t",sizeof(90000000000000));
	printf("%d",sizeof('A'));//size of character const is 4byte
	return 0;
}
