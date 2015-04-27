//Case expression cannot be constant variable and const string.Case expression can be macro, enum and character and integer constant.
//duplicate case is not posible.Case expression must be integral constant expression. If it is not integer then it is automatically type casted into integer value.
//switch expression must return an integer value. It cannot be float, double or long double.
//it is possible a switch case statement without any case but it is meaning less.
//We cannot use continue keyword in switch case. It is part loop.We can not declare any variable in any case of switch case statement.
#include<stdio.h> 
int main()
{
int var=10;
switch(10)	/* switch(any expression) */
{
	case 10:
		printf("successful");
		break;
}
return 0;
}
