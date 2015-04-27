#include<stdio.h> //find out size without sizeof operator 
struct  ABC
{
int a;
float b;
char c;
};
int main()
{
struct ABC *ptr=(struct ABC *)0;
ptr++;
printf("Size of structure is: %d",*ptr);
return 0;
}			    }
