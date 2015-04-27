#include<stdio.h>
void main()
{
char *str="ONE"
str++;
switch(str)//case expression cannot be a sting const
{
case "ONE":printf("Brazil");
break;
case "NE": printf("Toy story");
break;
case "N":  printf("His Girl Friday");
break;
case "E":  printf("Casino Royale");
} 
}
