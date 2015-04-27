#include<stdio.h>
int main()
{
	char *p;
	int a=3;
	printf("(*p)=%d ,(p)= %d\n",sizeof(*p),sizeof(p)); 
	printf("sizeof(6.5)=%d,sizeof(0.3f)=%d,sizeof(0.3l)=%d\n",sizeof(6.5),sizeof(0.3f),sizeof(0.3l));
	printf("sizeof(90000)=%d\n",sizeof(90000));
	printf("sizeof(\"a\")=%d\n",sizeof("a"));
	printf("sizeof('a')=%d\n",sizeof('a'));
	printf("sizeof(void)=%d\n",sizeof(void));
	printf("sizeof(a)=%d\n",sizeof(++a));
	printf("a=%d\n",a);
	printf("sizeof(a)=%d\n",sizeof(a=15/2));
	printf("a=%d\n",a);
return 0;
}
