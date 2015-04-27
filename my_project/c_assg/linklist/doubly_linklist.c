#include<stdio.h> 
#include<stdlib.h> 
struct node 
{
	int info;
	struct node *link;
	struct node *prev;
};
struct node *start;
	int count=0;
int main()
{
	int choice,n,m,i;
	 while(1)
	 {
	 	printf("1.create list\n");
		printf("2.add at begining\n");
		printf("3.display \n");
		printf("4.addafter\n");
		printf("5.delete\n");
		printf("6.serch\n");
		printf("7.reverse\n");
		printf("8.sorting linklist\n");
		printf("9.remove duplicate\n");
		printf("10.quit\n");
		printf("enter your choice :\n");
		scanf("%d",&choice);
	   	switch(choice)
	   	{
	   		case 1:
	   			start = NULL;
	   			printf("how many nodes you want to enter :\n");
	   			scanf("%d",&n);
	   			for(i=0;i<n;i++)	
	   			{
	   				printf("enter the element:\n");
	   				scanf("%d",&m);
	   				create_list(m);
				}
				break;
			case 2:
				display();
				break;
		}
	 }
	 return 0;
}
create_list(int data)
{
	struct node *local,*tamp;
	tamp=malloc(sizeof(struct node));
	tamp->info=data;
	tamp->link=NULL;
	if(start==NULL)
	{
		printf("starting doubly linklist\n");
		start=tamp;
		tamp->prev=start;
		count++;
	}
	else
	{
	printf("in------------>>>>>>>>>>>>>>>>>>>>\n"); 	
		local=start;
		while(local->link!=NULL)
		{
		printf("---------------------->...............>>.\n"); 
			local=local->link;
		}
		tamp->prev=local->prev;
		local->link=tamp;
		count++;
		printf("count=%d\n",count); 
	}
	return 0;
}
display()
{
	struct node *local;
	local=start;
	if(start==NULL)
	{
		printf("list is empty :\n");
		return 1;
	}
	printf("listis : \n"); 
	while(local!=NULL)
	{
		printf("%d\n",local->info); 
		local=local->link;
	}
	printf("%d\n",local->link); 
return 0;
}
