#include<stdio.h> 
#include<stdlib.h> 
int main(int argc , char *argv[])
{
	int i=1;
	int c;
	int num_args=0;
	FILE *fp;
	if(argc == 1)
	{
		fprintf(srderr,"no input files\nusage: cat file...\n");
		exit(1);
	}
	if(argc>1)
	printf("%d files to be displayed\n",argc - 1);
	num_argc=argc - 1;
	while(num_args > 0)
	{
		printf("[displaying files %s]\n",argv[i]);
		num_args--;
		fp = fopen(argv[i],"r");
		if(fp == NULL)
		{
			fprintf(stderr,"cnot display %s\n",argv[i]);
			continue ;
		}
		c = getc(fp);
		while(c!=EOF)
		{
			putchar(c);
			c = getc(fp);
		}
		fclose(fp);
		printf("\n[end of %s]\n................\n\n",argv[i]);
		i++
	}
}
