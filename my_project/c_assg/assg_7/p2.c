#include<stdio.h> 
int main()
{
	FILE *in;
	if(in = fopen("fred.txt","rt"))
	{
		for(char c;!feof(in);fscanf(in,"%c",&c));
		fclose(in);
	}
	return 0;
}
