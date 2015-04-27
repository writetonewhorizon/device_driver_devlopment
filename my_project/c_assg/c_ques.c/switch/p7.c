nclude<stdio.h>
void main()
{
//Case expression must be integral constant expression. If it is not integer then it is automatically type casted into integer value.so. (int)6.0f = 6,(int)6.0 = 6,(int)6.0L = 6,In c duplicate case is not possible.
switch(6)
{
case 6.0f:printf("Sangakkara");
break;
case 6.0: printf("Sehwag");
break;
case 6.0L:printf("Steyn");
break;
default:  printf("Smith");
} 
}
