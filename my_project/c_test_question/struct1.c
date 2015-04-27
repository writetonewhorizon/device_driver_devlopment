#include<stdio.h> 
int main()
{

	struct dharm
	{
		int age;
		char name;
		struct sharma
		{
			int age;
			char name;
		}dharm;
		int arr[4];
	}sharma={20,'d',21,'s',{3,4,5,6}};
	printf("sizeof structure =%d\n",sizeof(sharma));
	printf("%d %d %d %d %d\n",sharma.age,sharma.name,sharma.dharm.age,sharma.dharm.name,sharma.arr[1]);
	return 0;
}
