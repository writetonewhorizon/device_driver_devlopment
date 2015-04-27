#include<stdio.h>
#include<string.h> 
int main()
{
	int i=0,j,len;
	char arr[30];
	printf("enter the string : ");
	gets(arr);
	printf("%s\n",arr);
	len = strlen(arr);
	printf("len = %d\n",strlen(arr));
	for(i=0;arr[i]!='\0';i++)
	{
		if(arr[i] == '#')
		{
		arr[i]='!';
		printf("arr[%d]=%c\n",i,arr[i]);
		continue;
		}
		else if(arr[i]!= '!')
		{
		//arr[i]='!';
		printf("arr[%d]= %c\n",i,arr[i]);
		}
		else if(arr[i]=='!')
		{
			for(j=len-1;j>i;j--)
			{
				arr[j+1]=arr[j];
			}
			arr[i+1]='!';
			i++;
		}
		printf("arr=%s\n",arr);

	}

	return 0;

}
