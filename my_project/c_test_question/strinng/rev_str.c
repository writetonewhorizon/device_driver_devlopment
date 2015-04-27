#include<stdio.h>
#include<string.h> 
int main()
{
	int i,j;
	char array[]="Dharmender";
	char ch=0;
	j=strlen(array)-1;
	printf("j=%d",j);
	for(i=0;i<j;i++,j--)
	{
		ch=array[j];
		array[j]=array[i];
		array[i]=ch;
	}
	printf("%s\n",array);
	return 0;
}
