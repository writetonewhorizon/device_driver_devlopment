#include<stdio.h>
int stringcmp(char *dest,char *src)
{
	while(*dest++==*src++);
	return dest-src;
}
int main()
{
	char *dest="dharmender";
	char *src="sharma";
	int ret=0;
	ret=stringcmp(dest,src);
	if(ret==0)
		printf("string are equal\n");
	else if(ret<0)
		printf("destination string is small\n");
	else
		printf("destination string is bigger\n"); 
return 0;
}
