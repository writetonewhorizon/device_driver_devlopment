#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
int main()
{
      
char *p1= "name";
//int c =0;
//p1=(char *)malloc(20);
//memset (p1, '\0', 20);
char *p2;
char *p3;
p3=p2=(char *)malloc(20);
memset (p2, '\0', 20);
while(*p2++ = *p1++);
//{
//*p2++ = *p1++;
//	printf("c=00%d    ..%c..   %c\n",++c,*p2,*p1);
//};
printf("%s\n",p2);
printf("%s\n",p3);
return 0;
} 
