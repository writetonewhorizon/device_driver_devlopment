#include<stdio.h> 
int main(int argc , char *argv[])
{
	if(argc!=3)
	printf("usage:\n %sinterger1 integer2\n",argv[0]);
	else
	printf("%s + %s = %d\n",argv[1],argv[2],atoi(argv[1]+atoi(argv[2])); 
	return 0;
}	
