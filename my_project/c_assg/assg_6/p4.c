#include<stdio.h>

int main()
{
	static char *s[] = {"black", "white", "pink", "pink", "violet"};
	char **ptr[] = {s+4,s+3, s+2, s+1, s}, ***p;
	p = ptr;
	++p;
	printf("%s", **p+1);
	return 0;
}
