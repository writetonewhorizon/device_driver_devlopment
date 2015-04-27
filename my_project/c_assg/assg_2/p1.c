#include<stdio.h> 
int main()
{
	int x,y=1,z;
	if(y!=0)x=5;
	printf("%d\n",x);
	printf("%d\n",y);
	if(y===0)x=3;
	else x=5;
	printf("%d\n",x);
	printf("%d\n",y);
	x=1;
	if(y<0)if(y>0)x=3;
	else x=5;
	printf("%d\n",x);
	printf("%d\n",y);
	if(z=y<0)x=3
	else if(y==0)x=5;
	else x=7;
	printf("%d\n",x);
	printf("%d\n",y);
	printf("%d\n",z); 
	if(z=(y==0))x=5;
	x=7;
	printf("%d\n",x);
	printf("%d\n",y);
	printf("%d\n",z);
	if(x=y=z)x=3;
	printf("%d\n",x);
	printf("%d\n",y);
	printf("%d\n",z);
	return 0;
}
