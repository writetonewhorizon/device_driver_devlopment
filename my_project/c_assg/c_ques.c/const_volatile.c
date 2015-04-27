#include<stdio.h>
extern int dharm;
int dharm;
volatile const int z=10;
int func(void);
int main()
{
	printf("value of dharm is %d\n",dharm);
	printf("value of dharm is %p\n",&dharm);
	printf("value of data before is %d\n",z);
	func();
	printf("value of data after is %d\n",z);
	printf("value of dharm is %p\n",&dharm);
return 0;
}
int my_name()
{
	dharm=60;
	return dharm;
}
