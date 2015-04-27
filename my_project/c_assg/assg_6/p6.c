#include<stdio.h>

void main(char argc,int * argv[])
{

int count;
printf("%d\n",argc-1);
for(count=1;count<argc;count++)
printf("%d: %s\n",count,argv[count]);
printf("\n");

}


