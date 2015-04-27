#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
int main()
{
	
	char *tel_no;
	char *token;
	char *phone_no;
	tel_no=(char *)malloc(15);
	printf("enter the telephone number : ");
	scanf("%s",tel_no);
	token=(char *)malloc(8);
	phone_no=(char *)malloc(11);
	strncpy(token,tel_no,3);
	printf("%s\n",token);
	strcat(token,tel_no+9);
	printf("area code is%s\n",token);
	strcpy(phone_no,tel_no+3);
	printf("phone no is %s\n",phone_no);


}
