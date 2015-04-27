#include<stdio.h>
#include<string.h> 
int main()
{
	char array[]="dharmender sharma ece 431";
	char *str=array;
	char ch;
	int i,j=strlen(str)-1;
	printf("j=%d\n",j);
	for(i=0;i<j;i++,j--)
	{
		ch=*(str+j);
		*(str+j)=*(str+i);
		*(str+i)=ch;
		printf("%c\n",*(str+i)); 
	}
	printf("%s\n",str); 
	return 0;

}
