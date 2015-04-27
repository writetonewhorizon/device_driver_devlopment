#include<stdio.h>
void main()
{
	char c=256;
	char *ptr="Leon";
	if(c==0)
		while(!c)
			if(*ptr++)
				printf("%+u",c);
			else
				break;
}
