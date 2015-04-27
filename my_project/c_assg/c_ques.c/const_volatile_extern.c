#include<stdio.h>
extern int z;
int z ;
int dharm = 40;
void func()
{
	printf("dharm = %d \n",dharm); 
	z=30;
	dharm = my_name();
	printf("dharm = %d \n",dharm); 
}
	
