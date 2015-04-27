#include<stdio.h>
#define L 10 //case expression may be macro constant
void main()
{
//int L=10;
auto money=10;
switch(money,money*2)
{
case L:  printf("Willian");
break;
case L*2:printf("Warren");
break;
case L*3:printf("Carlos");
break;
default: printf("Lawrence");
case L*4:printf("Inqvar");
break;
}  
}
