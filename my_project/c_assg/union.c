#include<stdio.h> 
union result
{
	int marks;
	char grade;
	char arr;
	float per;
}res;
int main()
{
	res.marks=85;
	printf("marks=%d %p\n",res.marks,&res.marks);
	printf("sizeof(res.marks) =%d\n",sizeof(res.marks));
	res.grade='A';
	printf("grade=%c %p\n",res.grade,&res.grade);
	printf("sizeof(res.grade) =%d\n",sizeof(res.grade));
	res.arr='B';
	printf("arr=%c %p\n",res.arr,&res.arr);
	printf("sizeof(res.arr) =%d\n",sizeof(res.arr));
	res.per=85;
	printf("per=%d %p\n",res.per,&res.per);
	printf("sizeof(res.per) =%d\n",sizeof(res.per));
	printf("res=%p\n",&res);
	printf("sizeof union =%d\n",sizeof(res));
return 0;
}
