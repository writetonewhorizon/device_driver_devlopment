 #include<stdio.h>
 union group
 {
 	char xarr[2][2];
 	char yarr[4];
 };
 void main()
 {
 	union group x={'A','B','C','D'};
 	printf("%c",x.xarr[x.yarr[2]-67][x.yarr[3]-67]);
 }
