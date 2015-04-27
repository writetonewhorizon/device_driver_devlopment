#include<stdio.h>
int DTAC(int,char);
int main()
{
	int a,ret;
	char c;
	printf("enter the value which you want to convert : ");
	scanf("%d",&a);
	printf("enter the conversation name : \n "); 
again:	scanf("%c",&c);
	if(c=='\n')
		goto again;
	printf("a = %d\n",a);
	printf("a = %o %p\n",a,&a); 
	printf("a = %x %p\n",a,&a); 
	printf("a = %p\n",&a); 
	ret = DTAC(a,c);
	return 0;
}
int DTAC(int a,char c)
{
	printf("begin : %s\n",__func__); 
	int i=0,j;
	int arr[30];
	switch(c)
	{
		case 'b':
			while(a!=0)
			{
				arr[i] = a%2;
				printf("%d",arr[i]); 
				a=a/2;
				i++;
			}
			for(j=i-1;j>=0;j--)
			{
				printf("%d",arr[j]); 
			}
			printf("\n"); 
			break;
		case 'o':
			printf("a = %o %p\n",a,&a); 
			break;
		case 'x':
			printf("a = %x %p\n",a,&a);
			break;
	}
	printf("end :%s\n",__func__);
return 0;
}
