#include<stdio.h>
#include<string.h>
int main()
{
         char ch[31];
	 int i=0;
	 for(i=0;i<30;i++)
	 {
         printf("enter a character : %d",i);
again:   ch[i]=getchar();
	 if(getchar()=='\0')
	 	goto again;
	 printf("%c\n",ch[i]);
         printf("entered character is: ");
         putchar(ch[i]);
	 printf("\n");
	 }
         return 0;
}
