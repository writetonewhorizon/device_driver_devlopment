#include<stdio.h>
int main()
{
int i,n,k=0,l,arr[10],arr1[10];
printf("Enter any 10 numbers\n");
for(i=0;i<10;i++)
scanf("%d",&arr[i]);
printf("Enter any number \n");	
scanf("%d",&n);
printf("Now enter intex number \n");	
scanf("%d",&l);

for(i=0;i<10;i++)
{
	if(i==l)
	{
		arr1[k]=n;
		k++;
		break;	
		}	
		else
		{	
		arr1[k]=arr[i];
		k++;
		}
	}

	for(i=l;i<9;i++)
	{
		arr1[k]=arr[i];																	  k++;
	}
	for(i=0;i<9;i++)
	{
		printf("arr1[%d]=%d\n",i,arr[i]);
	}
}
