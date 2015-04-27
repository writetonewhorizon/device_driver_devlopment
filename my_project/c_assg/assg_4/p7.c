#include<stdio.h>
int main()
{
int i,k,arr[10],n,j=0,arr1[10];
printf("Enter any 10 numbers\n");
for(i=0;i<10;i++)
scanf("%d",&arr[i]);
printf("Now enter any number which is already present in the above mentioned array\n");
scanf("%d",&n);
for(i=0;i<10;i++)
{
	if(arr[i]==n)
	break;
	else
	{
		arr1[j]=arr[i];
		j++;
	}
}
i=i+1;
printf("i=%d\n",i); 
for(k=i;k<10;k++)
{
	arr1[j]=arr[k];
	j++;
}
arr1[10]='\0';
for(k=0;k<10;k++)
{
	printf("arr1[%d]=%d\n",k,arr1[k]);
}
return 0;
}
