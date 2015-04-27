#include<stdio.h> 
int main()
{
	int num=0x12345678;
	int tamp=0;
	printf("%x\n",num);
	while(num)
	{
		tamp=tamp|(num&0xf);
		num=num>>4;
		tamp=tamp<<4;
	}
	printf("%x\n",tamp);
return 0;
}
