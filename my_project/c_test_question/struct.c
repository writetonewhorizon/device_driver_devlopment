#include<stdio.h> 
int main()
{

	struct field
	{
		int age;
		char name;
	}dharm={20,'d'};
	char *ptr;
	ptr=(char *)&dharm;
	*ptr='s';
	printf("%d\n",dharm.age);
	ptr=ptr+4;
	printf("%d\n",*ptr);
	return 0;
}
