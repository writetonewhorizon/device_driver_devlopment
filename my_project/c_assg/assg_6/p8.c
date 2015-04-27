#include<stdio.h>
int main()
{
	int a[]={1,2,3,0,7,6,5,0,5,4,3,0};
	int *p,i,len,count=0;
	p=a;
	for(i=0;i<sizeof(a)/4;i++)
	{
		if(*(p+i)==0)
			continue;
		else
			count+=1;
	}
	printf("count=%d\n",count);

}
