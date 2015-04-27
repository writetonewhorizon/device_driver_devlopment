#include<stdio.h> 
int main()
{
	enum day {sunday,monday,thuday,wednesday,thursday,friday,saturday};
	enum day today;
	today = monday;
	if(today == saturday)
	printf("today is half day %d\n",today);
	else if(today== wednesday)
	printf("today is fullday\n");
	else
	printf("today is hollyday\n");
	int i;
	for(today;today<=6;today++)
	{
		
		switch(today)
		{
			case 0:
				printf("today is sunday %d\n",today);
				break;
			case 1:
				printf("today is monday %d\n",today);
				break;
			case 2:
				printf("today is tusday %d\n",today);
				break;
			case 3:
				printf("today is wednesday %d \n",today);
				break;
			case 4:
				printf("today is thursday %d\n",today);
				break;
			case 5:
				printf("today is friday %d\n",today);
				break;
			default:
				printf("today is saturday %d\n",today);
				break;
		}
		
	}
	return 0;
}
