#include<stdio.h> 
int main(int argc , char *argv[])
{
	if(argc == 1)
	printf("error\n"); 
	printf("%c\n",*(argv[1] + 1)); 
	printf("%c\n",(*(argv + 1))[2]); 
	printf("%c\n",argv[2][2]); 
}
