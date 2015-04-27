#include<stdio.h> 
#include<stdlib.h>
#include<string.h> 
struct Foo
{
  char *pName;
}*obj;
int main()
{
	printf("%d\n",sizeof(obj));
	obj= malloc(sizeof(obj));
	printf("%d\n",sizeof(obj));
	strcpy(obj->pName,"Your");
	//obj->pName="ramayan vs mahabhart";
	printf("%s\n", obj->pName);
	printf("%d\n",sizeof(obj->pName));
	return 0;
} 
