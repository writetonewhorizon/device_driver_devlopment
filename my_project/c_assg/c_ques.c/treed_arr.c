#include<stdio.h> 
int main()
{
	int i;
	int a[2][3][2]={ 
				{
					{ 22,4},{7,8},{3,43}
				},
				{ 
					{21,26},{28,33},{30,42}
				}
			};
		printf("%u\n",a); 
		printf("%u\n",*a); 
		printf("%u\n",**a); 
		printf("%u\n",***a); 
		printf("%u\n",a+1); 
		printf("%u\n",*a+1); 
		printf("%u\n",**a+1); 
		printf("%u\n",***a+1); 
		printf("%u\n",***a); 
		printf("%u\n",a+1);
		printf("%u\n",***a); 
		for(i=1;i<12;i++)
		{
		printf("%u\n",*(**a+i)); 
		}
		//printf("%u\n",***a+1); 
		//printf("%d\n",*(*(*(a+0)+0)+0)); 
	//	printf("%d\n",*(*(*(a+1)+2)+1)); 
}
