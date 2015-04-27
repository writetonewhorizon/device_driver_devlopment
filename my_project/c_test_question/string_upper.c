#include<stdio.h> 
int main()
{
	char array[20];
	int i=0;
	printf("enter the string to conver upper case to lower case\n"); 
	scanf("%s",array);
	printf("Entered string is %s\n",array);
	while(array[i]>=65 && array[i]<=92)
	{
		array[i]=array[i]+32;
		i++;
	}
	printf("converted string is %s\n",array); 
return 0;
}
