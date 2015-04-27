#include<stdio.h> 
void main()
{
struct bitfield
{
unsigned a:5;
unsigned c:5;
unsigned b:6;

}bit;
char *p;
struct bitfield *ptr,bit1={1,3,3};
p=&bit1;
p=p+1;
printf("%d",*p);
}
