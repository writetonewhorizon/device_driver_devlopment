#include<stdio.h> 
main()
{
	char *ptr;
	ptr = strtok("jan:feb,mar",":");
	printf(ptr);
	do
	{
		ptr=strtok('\0',":");
		if(ptr)
		printf("%5s\n",ptr); 
	}while(ptr);
}
