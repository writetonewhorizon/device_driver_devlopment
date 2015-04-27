#include<stdio.h>
void main()
//280 is beyond the range of unsigned char. Its corresponding cyclic value is: 24.In c switch case statement program control always move from the case which satisfy the switch condition and end with either break keyword, terminating} or any null character which will come first.
{
unsigned char c=280;
switch(c){
printf("Start\t");
case 280:printf("David Beckham\t");
case 24: printf("Ronaldinho\t");
default:  printf("Ronaldo\t");
printf("End");
}

}
