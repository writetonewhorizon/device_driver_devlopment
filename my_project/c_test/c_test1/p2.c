#include<stdio.h> 
void f(char *);
int main()
{
	f("123");
}
void f(char a[])
{
	if(a[1]  == '\0')
	return ;
	f(a+1);
	f(a+1);
	printf("%c\n",a[1]); 

}
