#include<stdio.h> 
int main()
{
	char byte;
	printf("enter the byte\n");
	scanf("%c",&byte);
	printf("%d",byte = byte<<4 | byte>>4);
return 0;
}
