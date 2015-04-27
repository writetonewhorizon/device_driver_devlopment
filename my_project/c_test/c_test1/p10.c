#include<stdio.h> 
main()
{
	union 
	{
		struct
			{
				char c[2];
				char ch[2];
			}s;
		struct 
		{
			int i;
			int j;

		}st;	
	} u={12,1};
	printf("%d %d\n",u.st.i,u.st.j); 
	printf("%c %c\n",u.st.c,u.st.ch); 

}
