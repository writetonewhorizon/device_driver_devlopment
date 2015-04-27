#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    void *p1;
    void *p2,*p3;
    p1 = malloc(0);
    printf("p1=%p\n",p1);
    p2 = realloc(p1, 1024);
    printf("p2=%p\n",p2);
    p3 = realloc(p1, 0);
    printf("p3=%p\n",p3);
    if (p1 == p2)
	    puts("possible, OK");
	/* Ignore the memory leaks */
	if (malloc(0) == realloc(malloc(0), 1024))
	puts("shouldn't happen, something is wrong");
return 0;
}
