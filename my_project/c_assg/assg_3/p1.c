#include<stdio.h>
int main()
{
	int x,y,z;
	x=y=z=0;
	while(y<10)++y;x+=y;
	printf("%d\n",x); 
	printf("%d\n",y); 
	printf("%d\n",z);
	x=y=0;
	while(y<10)x+=++y;
	printf("%d\n",x); 
	printf("%d\n",y); 
	printf("%d\n",z);
	x=1;
	while(y<10)
	{
		x=y++;z=++y;
	}
	printf("%d\n",x); 
	printf("%d\n",y); 
	printf("%d\n",z);
	for(y=1;y<10;y++)x=y;
	printf("%d\n",x); 
	printf("%d\n",y); 
	
	for(y=1;(x=y)<10;y++);
	{	
	printf("%d\n",x); 
	printf("%d\n",y); 
	}
	for(x=0,y=1000;y>1;x++,y/=10)
	{
	printf("%d\n",x); 
	printf("%d\n",y); 
	}
return 0;
}
