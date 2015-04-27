#include<stdio.h>
void main()
{	//We cannot use continue keyword in switch case. It is part loop.
static int i;
int j=1;
int arr[5]={1,2,3,4};
switch(arr[j])
{
case 1: i++;break;
case 2: i+=2;j=3;continue;
case 3: i%=2;j=4;continue;
default: --i;
}
printf("%d",i);  
}
