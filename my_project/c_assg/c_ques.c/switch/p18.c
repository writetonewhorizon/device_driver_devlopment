nclude<stdio.h>
void main()
{
//Consider on the expression:
//a=a==b==0;
//a=(a==b)==0; //Since associate is right to left
//a =(3==2)==0
//a=0==0
//a=1
//
//switch case will not affect the value of variable a.
//Also sizeof operator doesn't affect the value of the any variable
int a=3,b=2;
a=a==b==0;
switch(1)
{
a=a+10;
}
sizeof(a++);
printf("%d",a); 
}
