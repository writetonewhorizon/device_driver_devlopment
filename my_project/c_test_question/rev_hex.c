#include<stdio.h> 
int main()
{
	int y=0;
	int x=0x12345678;
//	swapped = ((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000);
	while(x)
	{
		y|=(x&0xf);
		x=x>>4;
		y=y<<4;
	}
	printf("%x",y);
return 0;
}
