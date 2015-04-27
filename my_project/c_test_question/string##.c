#include<stdio.h>
#define call(x,y) x##y
int main(){
int x=5,y=10,xy=20;
printf("%d",xy+call(x,y));
return 0;
}
