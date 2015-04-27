#include<stdio.h> 
int main()
{
	struct main
	{
		unsigned char ch: 3;
		short int ch1: 13;
		unsigned char ch2: 1;
	}dharm={2,256,1};
	char *ptr=(char *)&dharm;
	printf("%d %d %d \n",dharm.ch,dharm.ch1,dharm.ch2);
	printf("%d\n",sizeof(dharm));
	++ptr;
	printf("%d\n",*ptr);
	return 0;
}
