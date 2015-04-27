#include<stdio.h> 
void    main()
        {
	        int x=20,y=35;
		        x=y++ + x++;
				        printf("%d%d\n",x,y);
			        y= ++y + ++x;
				        printf("%d%d\n",x,y);

					    }

