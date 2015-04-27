#include<stdio.h> 
int main()
{
	char array[4];
	int i=0,sum=0;
	printf("enter the string\n");
	scanf("%s",array);
	while(array[i]!='\0')
	{
		if(array[i]>=48 || array[i]<=57)
		{
			sum=sum*10+(array[i]-48);
			i++;
		}

		else 
			break;
	}
	printf("intiger value is %d\n",sum); 
return 0;
}
