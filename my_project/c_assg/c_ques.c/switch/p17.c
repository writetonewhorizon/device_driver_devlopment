nclude<stdio.h>
void main()
{
int a=5;
a=a>=4;
switch(2){
case 0:int a=8;//We can not declare any variable in any case of switch case statement.
case 1:int a=10;
case 2:++a;
case 3:printf("%d",a);
}
}
