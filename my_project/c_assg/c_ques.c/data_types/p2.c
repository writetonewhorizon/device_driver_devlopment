#include<stdio.h>
int main(){
    signed x,a;
        unsigned y,b;
	    a=(signed)10u;
	        b=(unsigned)-10;
		    y = (signed)10u + (unsigned)-10;
		        x = y;
			    printf("%d  %u\t",a,b);
			        if(x==y)
				         printf("%d %d",x,y);
					     else if(x!=y)
					              printf("%u  %u",x,y);
						          return 0;
							  }
