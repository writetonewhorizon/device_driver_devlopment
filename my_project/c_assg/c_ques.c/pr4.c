#include<stdio.h> 
struct student
{
int a;
 int b;
extern int c;
int d;
}s={6,7,8,9};
void main()
{
printf("%d %d % %d",s.a,s.b,s.c,s.d);
}
