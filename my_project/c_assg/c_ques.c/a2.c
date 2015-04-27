#include<stdio.h>
main()
{
	struct xx
	{
		int x;
		int arr[5];
	//char name;
	};
	struct xx s;
	s={1,2,3,4,55,6,7};
	//s.x=20;
	//s.name="name";
	printf("%d\n",s.x); 
//	printf("%s\n",s.name); 
	printf("%d\n",s.arr); 
}
