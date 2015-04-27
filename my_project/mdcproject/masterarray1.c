#include<stdio.h>
//#include"header.h"
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	char *marray;
	char c,r[44];
	int i,j,x,k = 0;
	int count = 0;
//	marray = (char *)malloc(sizeof(char));
//	printf("%d\n",sizeof(*marray));
/*	FILE *fp;
	fp = open("singh.c","r");
	c = getc(fp);
	*marray = c;
	c = getc(fp);
	printf("%c %c\n",c,*marray);
	fputc(marray,fp);*/
	int fq;
	fq = open("singh.c",O_RDONLY);
	x = read(fq,&r,44);
	printf("%s\n",r);
	printf("Master array is\n");
//	printf("%c\n",*marray);
//	c = *marray;
	
	
	/*while(c != EOF)
	{
		count++;
		for(i = 0;i < count;i++)
		{
			if(c != *marray)
			{
				marray = realloc(marray,sizeof(marray + 1));
				printf("%c %d\n",*marray,sizeof(marray));
			
			}

		
		}


	}*/
//	c = r[0];
	for(i = 0;i < 50;i++)
	{
		count++;
		c = r[i];
		if(i == 0)
		{
			marray = malloc(sizeof(char));
			*marray = c;
			printf("%c",*marray);
			continue;
		
		}
		else if(c != EOF)
		{
			for(j = 0;j < count-1;j++)
			{
				if(c != r[j] && j == count - 2)
				{
					k++;
					marray = realloc(marray,sizeof(marray+k));
					*(marray+k) = c;
					printf("%c",*(marray+k));
				}
				else if(c != r[j])
					continue;
				else
					break;

			}
			
		
		}
	
	}
	printf("%d\n",k);
	printf("size of master array is :%d\n",sizeof(marray + k));
//	printf("%d\n",sizeof(*marray));


	return 0;





}
