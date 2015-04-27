#include<stdio.h>//calls two or three func without if lse or switch condition 
int fun();
int fun1();
int fun2();
int main()
{
	int i;
	int (*ptr[2])();
	ptr[0]=&fun;
	ptr[1]=&fun1;
	ptr[2]=&fun2;
	printf("main func is working :  \n");
	printf("enter the value \n"); 
	scanf("%d",&i);
	ptr[i]();
	//fun();
	//fun1();
	//fun2();
	return 0;
}
int fun()
{
	printf("initilization of %s\n",__func__);
	printf("end of %s\n",__func__);
	return 0;
}
int fun1()
{
	printf("initilization of %s\n",__func__);
	printf("end of %s\n",__func__);
	return 0;
}
int fun2()
{
	printf("initilization of %s\n",__func__);
	printf("end of %s\n",__func__);
	return 0;
}
