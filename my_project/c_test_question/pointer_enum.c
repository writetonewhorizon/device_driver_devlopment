#include<stdio.h>
int main()
{
	static char *s[3]={"math","phy","che"};
	typedef char *( *ppp)[3];
	static ppp p1=&s,p2=&s,p3=&s;
	char * (*(*array[3]))[3]={&p1,&p2,&p3};
	char * (*(*(*ptr)[3]))[3]=&array;
	p2+=1;
	p3+=2;
	printf("%s",(***ptr[0])[2]);
return 0;
}
