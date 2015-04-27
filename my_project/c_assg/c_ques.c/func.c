#include<stdio.h> 

int x;
int modifyvalue()
{
	return(x+=10);
}

int changevalue(int x)
{
	return(x+=1);
}    
void main()
{
	int x=10;
	x++;
	changevalue(x);
	x++;
	modifyvalue();
	printf("First output:%dn",x);
	
	x++;
	changevalue(x);
	printf("Second output:%dn",x);
	modifyvalue();
	printf("Third output:%dn",x);
//return 0;
} 
