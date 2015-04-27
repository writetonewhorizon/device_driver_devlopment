#include<stdio.h>
void main()
{	//ASCII value of the character constant 'A' is 65 and 'a' is 97,Nesting of switch case is possible in c.
char *str="cquestionbank.blogspot.com";
int a=2;
switch('A')
{
case 97:
	switch(97)
	{
	default: str+=1;
	}
case 65:
	switch(97)
	{
	case 'A':str+=2;
	case 'a':str+=4;
	}
default:
for(;a;a--)
str+=8;
}
printf("%s",str); 
}
