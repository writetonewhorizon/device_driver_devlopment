#include<stdio.h> 
void main()
{
struct fi
{
int a;
char b;
}bit;
struct fi field_bit1={5,'A'};
char *p=&field_bit1;
*(p++)='b';
printf("\n%d %c",field_bit1.a,field_bit1.b);
}
