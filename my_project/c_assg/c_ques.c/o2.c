#include<stdio.h> 
main()
{
char *cptr,c;
void *vptr,vr;
c=10; vr=0;
cptr=&c; vptr=&vr;
printf("%c%v",c,vr);
}

