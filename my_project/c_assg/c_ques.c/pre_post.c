#include<stdio.h>
int main()
{
	int b;
	int a=1;
	b=a++/a++;
	printf("%d\n",b);
	a=1;
	b=++a/++a;
	printf("%d\n",b);
	a=2;
	b=++a + a++ + a++;
	printf("%d %d\n",b,a);
	a=3;
	b=a++ + a++ + ++a;
	printf("%d %d\n",b,a);
	a=4;
	b=++a + ++a + a++;
	printf("%d %d\n",b,a);
	a=5;
	b=++a + a++;
	printf("%d %d\n",b,a);
	a=5;
	b=++a + a++ + a++ + a++;
	printf("%d %d\n",b,a);
	a=7;
	b=++a + ++a ;
	printf("%d %d\n",b,a);
	a=7;
	b=a++ + a++ ;
	printf("%d %d\n",b,a);

}
