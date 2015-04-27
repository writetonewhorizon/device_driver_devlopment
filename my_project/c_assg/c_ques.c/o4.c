func(a,b)
int a,b;
{
return( a= (a==b) );
}
main()
{
int f1();
int process(),func();
f1(2,3,4);
printf("%d\n",f1(1,2,3,4));
printf("%d\n",f1(1,2,3));
printf("The value of process is %d !\n ",process(func,3,6));
}
process(pf,val1,val2)
int (*pf) ();
int val1,val2;
{
return((*pf) (val1,val2));
}
f1(a,b,c,d)
{
	printf("%d\n",a); 
	printf("%d\n",b); 
	printf("%d\n",c); 
	printf("%d\n",d); 
	return a+b+c+d;
}
