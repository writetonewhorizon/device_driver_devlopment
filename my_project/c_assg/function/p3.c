#include<stdio.h>
int z=0;
int f(int *x,int *m)
{
	int static kk=10;
	*x=*x+2;
	z=z+*m;
	kk=kk+*x;
	*m=kk;
	return *x+kk;
}
int main()
{
	int k=3,m=5,r=0,*p,z=f(&k,&r);
	printf("%d %d %d %d\n",k,m,r,z);
	p=&m;
	z=f(&m,&r);
	printf("%d %d %d %d %d\n",k,m,r,z,*p); 
	return 0;
}
