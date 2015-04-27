#include<stdio.h>
int main()
{
	double f_temp= 0;
	double c_temp =0;
	double k_temp = 0;
	printf("Enter the f_temp : ");
	scanf("%d",&f_temp);
	printf("%f\n",f_temp); 
	c_temp = 1.8 * f_temp + 32.0;
	k_temp = c_temp + 273.16;
	printf("f_temp = %.2f,c_temp = %.2f,k_temp = %.2f\n",f_temp,c_temp,k_temp); 
	return 0;
}
