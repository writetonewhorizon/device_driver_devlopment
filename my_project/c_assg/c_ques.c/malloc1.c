#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
	int i=1,n,state=0, k, dist;
	int** myMat;
	char *city1, *city2, **matnames;
	FILE* p;
	printf("\n");
	city1 = (char*) malloc(sizeof(char));
	city2 = (char*) malloc(sizeof(char));
	matnames = (char**) malloc(n * sizeof(char*));
	myMat = (int**) malloc(n * sizeof(int*));               
	printf("\n"); 
	p= fopen(argv[1],"r");
	/************************************************************/
	matnames[0] = (char*) malloc(sizeof(char));
	matnames[1] = (char*) malloc(sizeof(char));
	matnames[2] = (char*) malloc(sizeof(char));
	matnames[2] = NULL;
	fscanf(p, "%s %s %d", city1, city2, &dist);
	strcpy(matnames[0],city1);
	strcpy(matnames[1],city2);
	/************************************************************/  
	while( fscanf(p,"%s %s %d",city1,city2, &dist) != EOF)
	{             
		for(k=0; matnames[k]!=NULL; k++)
		{                   
			if( strcmp(matnames[k], city1) != 0)
			{
				state++;
			}               
		}       
		if(state  == k)
		{
			matnames[k] = (char*) malloc(sizeof(char));
			strcpy(matnames[k], city1);
			matnames[k+1] = (char*) malloc(sizeof(char));
			matnames[k+1] = NULL;
		}
        	state = 0;
		for(k=0; matnames[k] != NULL;k++)
		{                  
			if( strcmp(matnames[k], city2) != 0)
			{
	
				state++;
			}               
		}
		if(state == k)	
		{
			matnames[k] = (char*) malloc(sizeof(char));
			matnames[k+1] = (char*) malloc(sizeof(char));
			strcpy(matnames[k], city2); 
			matnames[k+1] = NULL;   
		}
		state = 0;
	
	}
	return 0;
}
