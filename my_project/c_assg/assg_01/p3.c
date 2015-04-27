#include<stdio.h> 
int main()
{
	int x,y,z;
	x=y=z=1;
	++x||++y&&++z;
	printf("%d\t%d\t%d\n",x,y,z);
	x=y=z=1;
	++x&&++y||++z;
	printf("%d\t%d\t%d\n",x,y,z);
	x=y=z=1;
	++x&&++y&&++z;
	printf("%d\t%d\t%d\n",x,y,z); 
	x=y=z=-1;
	++x&&++y||++z;
	printf("%d\t%d\t%d\n",x,y,z); 
	x=y=z=-1;
	++x||++y&&++z;
	printf("%d\t%d\t%d\n",x,y,z);
	x=y=z=-1;
	++x&&++y&&++z;
	printf("%d\t%d\t%d\n",x,y,z); 
	return 0;
}
