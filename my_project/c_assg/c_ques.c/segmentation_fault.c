#include<stdio.h> 
int main()
{
  struct xx
    {
     int x;
     char name[5];
		};
struct xx *s;
s->x=5;
printf("%d\n",s->x);
printf("%s\n",s->name);
printf("%p\n",&s->name);
return 0;
}
