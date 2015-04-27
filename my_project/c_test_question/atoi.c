#include<stdio.h>
#include<stdlib.h>

int main()
{
	char *i = "55.555";
	int result1 = 10;
	float result2 = 11.111;
	result1 = result1+atoi(i);
	result2 = result2+atof(i);
	printf("%d, %f", result1, result2);
return 0;
}
