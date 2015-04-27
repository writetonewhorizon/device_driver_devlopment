 #include<stdio.h>
 void main()
 {
 	long double a;
 	signed char b;
 	int arr[sizeof(!a+b)];
 	printf("%d",sizeof(arr));
 }
