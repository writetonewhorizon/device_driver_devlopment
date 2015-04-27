#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
struct sige
{
	short int f;
	int a;
	long int g;
	char b;
	float c;
	double d;
	long double h;
	char *e;

}*abc;
int main()
{
	//abc->f = 15;
	printf("%d %d %d %d %d %d %d %d\n",sizeof(abc->f),sizeof(abc->a),sizeof(abc->g),sizeof(abc->b),sizeof(abc->c),sizeof(abc->d),sizeof(abc->h),sizeof(abc->e));
	printf("%d\n",sizeof(struct sige));
	printf("%p\n",&abc);
	printf(" %p\n",&abc->f);
	//printf(" %d\n",abc->f);
	return 0;
}
