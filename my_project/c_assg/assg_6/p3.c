#include<stdio.h>

int main(void)
{
	int value = 77, num = 99;
	int *pv = &value, *pn = &num;
	int **ppi;
	ppi = &pv;
	printf("**ppi = %d\n", **ppi);
	ppi = &pn;
	printf("**ppi = %d\n", **ppi);
	system("pause");
}
