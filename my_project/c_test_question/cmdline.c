#include<stdio.h> 
int main(int argc,char *argv[])
{
	int count=0,i;
	for(i=0;i<argc;i++)
	{
		printf("%s\n",argv[i]);
		count++;
	}
	printf("%d %d\n",count,argc);
return 0;
}
