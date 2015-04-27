#include<stdio.h> 
#include<stdlib.h>
struct node 
{
	int info;
	struct node *link;
};
struct node *start;
int main()
{
	int choice,n,data,i;
	while(1)
	{
		printf(" 1 - create stack and Push\n");
		printf(" 2 - Pop\n");
		printf(" 3 - Dipslay\n");
		printf(" 4 - Exit\n");
		printf(" 5 - Stack Count\n");
		printf(" 6 - Destroy stack\n");
		printf("enter the choice\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("entre how many node you want to create:\n");
				scanf("%d",&n);
				start=NULL;
				for(i=0;i<n;i++)
				{
					printf("enter the data into the node\n");
					scanf("%d",&data);
					create_stack(data);
				}
				break;
			case 2:
				printf("poped item is :\n"); 
				pop();
				break ;
			case 3:
				printf("list is :\n"); 
				display();
				break;
			case 4:
				exit(0);
				break;
			case 5:
				count();
				break;
			case 6:
				destroy();
				break;
			default :
				printf("you entered wrong choice :\n");
				break;
		}
	}
	return 0;
}
create_stack(int data)
{
	struct node *local,*tamp;
	int count=0;
	tamp=malloc(sizeof(struct node));
	tamp->info=data;
	tamp->link=NULL;
	if(start==NULL)
	{
		start=tamp;
		count++;
		printf("count=%d\n",count); 
	}
	else
	{
		local=start;
		while(local->link!=NULL)
		{
			local=local->link;
		}
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
	while(local!=NULL)
	{
		printf("  %d\n",local->info); 
		local=local->link;
	}
	return 0;
}
pop()
{
	struct node *local;
	if(local==NULL)
	{
		printf("stack is empty : \n");
		return 1;
	}
	else
	{
		local=start;
		printf("%d\n",local->info); 
		start=local->link;
		free(local);
	}
	return 0;
}
count()
{
	struct node *local;
	int count=0;
	local=start;
	if(local==NULL)
	{
		printf("stack is empty\n");
		return 1;
	}
	else
	{
		while(local!=NULL)
		{
			local=local->link;
			count ++;
		}
		printf("the no of element in stack are =%d\n",count); 
	}
return 0;
}
destroy()
{
	struct node *local;
	local=start;
	if(local==NULL)
	{
		printf("stack is empty so cannot destroy it:\n");
		return 1;
	}
	else
	{
		while(local!=NULL)
		{
			local=start;
			printf("destroy element is %d\n",local->info); 
			if(!local->link)
			{
				printf("now their is no element in the stack to destroy:\n"); 
				break;
			}
			start=local->link;
			free(local);
		}
	}
	return 0;
}
