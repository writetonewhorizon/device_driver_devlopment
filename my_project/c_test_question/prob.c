#include<stdio.h>
int main()
{
	int a=2;
	a=a++ + ~++a;	//take two's complimant when nagative value is recived
	printf("%d",a);
return 0;
}
