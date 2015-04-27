#include<stdio.h>
/*maximum size is allocated to next data, suppose size of char after double is 8*/
struct data
{
	char i;
	int j;
	char b;
	int c;
	double d;
	char e;
	int f;
	double g;
	char h;
	char *k;
	int l;
}ram;
int main()
{
	/*1-3, 4 ,1-3, 4, 8, 1-7,1,4,8,8,8,8  = 64 */
	printf("size of structure = %d\n",sizeof(ram));
	printf("size of structure = %d\n",sizeof(struct data));
}
