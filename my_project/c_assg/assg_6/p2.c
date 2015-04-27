#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int *a, *s, i;
	s = a = (int *)malloc(4 * sizeof(int));	
	for(i=0;i<4;i++)
		*(a+i) = i * 10;
	printf("%d\n", *s++);
	printf("%d\n", (*s)++);
	printf("%d\n", *s);
	printf("%d\n", *++s);
	printf("%d\n", ++*s);
	for(i=0;i<4;i++)
	printf("%d\n",*(a+i));
	return 0;
}
