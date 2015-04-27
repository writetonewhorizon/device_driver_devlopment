#include<stdio.h> 
//iAs we know %s in prinf statement prints stream of characters until it doesn’t get first null character. Since array arr has not stored any null character so it will print garbage value. 
void main()
{
char arr[7]="Network";
printf("%s",arr);
}
