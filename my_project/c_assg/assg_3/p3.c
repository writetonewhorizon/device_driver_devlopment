#include<stdio.h>
#define FALSE 0
#define TRUE 1
charinput[]="p1=3.14159,approximately";
int main()
{
	char c;
	int done,high,i,in,low;
	i=low=in=high=0;
	while(c=input[i++]!='\0')
	{
		if(c<'0')low++;
		else if(c>'9')high++;
		else in++;
		printf("%c\n",done); 
		printf("%d\n",low);
		printf("%d\n",in);
		printf("%d\n",high); 
	}
	i=low=in=high=0;done=FALUSE;
	while(c=input[i++]!='\0'&&!done)
	{
		if(c<'0')low++;
		else if(c>'9')high++;
		else in++;
		if(low>=3 || high >=3 || in>=3)done=true;
		printf("%c\n",done); 
		printf("%d\n",low);
		printf("%d\n",in);
		printf("%d\n",high); 
	}
	i=low=in=high=0;done=FALSE;
	while(c=input[i++]!='\0'&&!done)
	{
		if(c<'0')done=(++low==3?TRUE:FALSE);
		else if(c>'9')done=(++high==3?TRUE:FALSE);
		else done=(++in==3?TRUE:FALSE);
		printf("%d\n",done); 
		printf("%d\n",low);
		printf("%d\n",in);
		printf("%d\n",high); 
	}
	
return 0;
}
