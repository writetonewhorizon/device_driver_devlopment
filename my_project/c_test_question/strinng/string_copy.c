#include<stdio.h> 
char *stringcopy(char *dest,char *source)
{
	int i=0;
	char *tamp;
	tamp=dest;
	while(*dest++=*source++);
	return tamp;
}
int main()
{
	char arr[]="dharmender";
	char *source="sharma";
	char *dest=arr;
	dest=stringcopy(dest,source);
	printf("%s\n",dest);
	return 0;
}
