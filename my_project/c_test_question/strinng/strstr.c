#include<stdio.h> 
char *stringstr(char *dest,char *src)
{
	int count=0;
	while(*dest)
	{
		if(*dest==*src)
		{
			src++;
			dest++;
			count++;
			if(*src=='\0')
			{
			return dest-count;
			}
		}
		else
		{
			if(count!='\0')
			{
				src=src-count;
				count=0;
			}
			dest++;
		}
	}
return (char *)0;
}
int main()
{
	char *dest="dharmenddder";
	char *src="de";
	char *pos;
	pos=stringstr(dest,src);
	printf("%p %s",pos,pos);
	return 0;
}
