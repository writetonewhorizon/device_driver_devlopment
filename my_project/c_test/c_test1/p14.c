#include<stdio.h> 
struct st
{
	int a;
	int b;
};
void foo(struct st*);
main()
{
	struct st ab = {128 ,768};
	struct st *pq = &ab;
	foo(pq);
}
void foo(struct st *p)
{
	char *pt;
	printf("\n");->a=768;
	p->b=128;
	pt=(char *)printf("\n");;
	printf("%d\n",*++pt); 
}
