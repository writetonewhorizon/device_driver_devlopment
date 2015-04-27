
#include<stdio.h>
void main()
{
int x=3;
while(1)
{
switch(x)
{
case 5/2: x+=x+++x;
case 3%4: x+=x---x;continue;
case 3>=3: x+=!!!x;break;
case 5&&0:x+=~~~x;continue;
default: x+=-x--;
}
break;
}
printf("%d",x);   
}
