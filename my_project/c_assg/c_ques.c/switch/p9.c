#include<stdio.h>
void main()
{		//Consider on the expression:5/2*6+3.0=2*6+3.0=12 + 3.0=15.0
		//In c switch expression must return an integer value. It cannot be float, double or long double
switch(5/2*6+3.0)
{
case 3:printf("David Beckham");
break;
case 15:printf("Ronaldinho");
break;
case 0:printf("Lionel Messi");
break;
default:printf("Ronaldo");
}  
}
