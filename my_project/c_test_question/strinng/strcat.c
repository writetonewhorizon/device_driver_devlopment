#include<stdio.h>
#include<string.h> 
char *stringcat(char*dest,char*source)
{
	char *tamp=dest;
	while(*dest)
		dest++;
	while(*dest++=*source++);
	return tamp;

}
int main()
{
	char array[20]="dharmender";
	char *dest;
	dest=array;
	char *source="sharma";
	dest=stringcat(dest,source);
	printf("%s",dest);
return 0;
}
