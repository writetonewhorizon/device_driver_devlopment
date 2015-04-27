nclude<stdio.h>
void main()
{	//It is possible to write label of goto statement in the case of switch case statement.
switch(2)
{
case 1L:printf("No");
case 2L:printf("%s","I");
goto Love;
case 3L:printf("Please");
case 4L:Love:printf("Hi");
} 
}
