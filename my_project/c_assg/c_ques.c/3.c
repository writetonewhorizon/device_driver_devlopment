    #define swap(a,b)    {  a=a+b;	 b=a-b;	 a=a-b;    }
//    #define swap(a,b) a=50;b=60;
#include<stdio.h>	
        void main()
	{
	int x=5, y=10;
	swap (x,y);
	printf("%d %dn",x,y);
	swap2(x,y);

	printf("%d %dn",x,y);
	}

  int swap2(int a, int b)
  {
  int temp;
  temp=a;
  b=a;
  a=temp;
  return 0;
  }

