#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>
int main()
{
	char *arr="dharmender sharka ece 431 2900 ggg";
	char *com,*comp,*decomp,*deco;
	char count_arr[10];
	int count=0,len=0;
	int flag=0;
	int i=0, j=1,k;
	int l=0;
	int m=1;
	//printf("enter the string for compression : \n");
	//scanf("%s",arr);
	len=strlen(arr);
	printf("len = %d\n",len); 
	while(*arr)
	{
		if(*arr==' ')
		{
			arr++;
			count_arr[i]=count;
			printf("count_arr[%d]=%d\n",i,count_arr[i]); 
			i++;
			count++;
			continue;
		}
		
			if(flag==0)
			{
				comp = (char *)malloc(1);
				com=comp;
				flag=1;	
			}
			else
			{
				comp = (char *)realloc(comp,++j);
			}
		*com=*arr;
		com++;
		arr++;
		count ++;

	}
	printf("Decompressed array is %s\n",comp);
	printf("compression programe is starting : \n"); 
	flag=0;
	for(k=0;k<len;k++)
	{
		
		if(k<count_arr[l])
		{
			if(flag==0)
			{
				deco=(char *)malloc(1);
				decomp=deco;
				*decomp=*comp; 
				decomp++;
				comp++;
				flag=1;
			}
			else
			{
				deco = (char *)realloc(deco,++m);
				*decomp=*comp;
				decomp++;
				comp++;
			}
		
		}
		else
		{
			
			deco = (char *)realloc(deco,++m);
			*decomp=' ';
			decomp++;
			l++;
		}
	}
		printf("%s\n",deco); 


}
