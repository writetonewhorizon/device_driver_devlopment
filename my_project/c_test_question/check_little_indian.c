#include<stdio.h> 
int main()
{

	short int a = 0x0002;
	char ch=(char)a;
	if(ch==2)
		printf("little indian\n");
	else
		printf("big indian"); 
}
