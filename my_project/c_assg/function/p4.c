#include<stdio.h>
min(int double,double y)
{ 
	printf("%d %d\n",x,y); 
	if(x<y)
		return x;
	else
		return y;

}
int main()
{
	double x,y,z;
	printf("enter the pai of double values : ");
	scanf("%f %f",&x,&y);
	z= min(x,y);
	printf("%f\n",z); 
	return 0;
}
