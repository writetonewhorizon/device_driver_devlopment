#include<stdio.h>
int dynamic(int,...);
int main()
{
	int x,y;
	x=dynamic(2,4,6,8,10,12,14);
	y=dynamic(3,6,9,12);
	printf("%d %d ",x,y);
return 0;
}
int dynamic(int s,...)
{
	void *ptr;
	ptr=...;
	(int *)ptr+=2;
	s=*(int *)ptr;
return s;
}
