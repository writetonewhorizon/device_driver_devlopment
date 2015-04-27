#include<stdio.h>
int main()
{
    int scanf=12;
    int EOF=10;
    char printf='a';
    putchar(printf);
    printf("%d",scanf);//Variable name cannot be pre defined function of included header file.
    printf("%d\n",EOF); 
    return 0;
    }
