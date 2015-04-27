#include <stdio.h>
#include <string.h>
int main()
{
	char *str = "Hello world";
	int count = strlen(str);
	str = str + count-1;
	while(count)
	{
		printf("%c", *str);
		str--;
		count--;
	}
return 0;
}
