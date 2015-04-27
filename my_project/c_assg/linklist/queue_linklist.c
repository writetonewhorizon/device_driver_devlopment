#include<stdio.h> 
#include<stdlib.h>
struct node
{
	int info;
	struct node *link;
};
struct node *rear,*front;
int main()
{
int choice,n,data,i;
while (1)
{
	printf(" 1 - Enque\n");
	printf(" 2 - Deque\n");
	printf(" 3 - Exit\n");
	printf(" 4 - Display\n");
	printf(" 5- Destroy\n"); 
	printf("\n Enter choice : ");
	scanf("%d", &choice);
	switch (choice)
	{
		
		case 1:
			printf("Enter how many node you want : ");
			scanf("%d", &n);
			rear=front=NULL;
			for(i=0;i<n;i++)
			{
				printf("enter the data in the queue\n"); 
				scanf("%d",&data);
				enqueue(data);	
			}
			break;
		case 2:
			dequeue();
			break;
		case 3:
			display();
			break;
		case 4:
			exit(0);
			break;
		case 5:
			destroy();
			break;
		default :
			printf("entered wrong choice please enter again\n"); 
			break;

	}

}
	return 0;
}
enqueue(int data)
{

	struct node *tamp;
	if(rear==NULL)
	{
		rear=malloc(sizeof(struct node));
		rear->info=data;
		rear->link=NULL;
		front=rear;
	}
	else
	{
		tamp=malloc(sizeof(struct node));
		tamp->info=data;
		tamp->link=NULL;
		rear->link=tamp;
		rear=tamp;
	}
	return 0;
}
display()
{
	struct node *tamp;
	int count=0;
	tamp=front;
	if(front==NULL)
	{
		printf("queue is empty:\n");
		return 1;
	}
	else
	{
		while(tamp!=NULL)
		{
			printf("data in %d queue is %d\n",count,tamp->info); 
			tamp=tamp->link;
			count++;
		}
	printf("count=%d\n",count); 
	}
	return 0;
}
dequeue()
{
	struct node *tamp;
	tamp=front;
	if(tamp==NULL)
	{
		printf("queue is empty:");
	}
	else
	{
		tamp=front;
		printf("dequeue data is %d\n",tamp->info); 
		front=tamp->link;
		free(tamp);
	}
	return 0;
}
destroy()
{
	struct node *tamp;
	if(front==NULL)
	{
		printf("queue is empty\n"); 
	}
	else
	{
		
		while(front!=NULL)
		{
			tamp=front;
			printf("dequeue data is %d\n",tamp->info); 
			front=tamp->link;
			free(tamp);
		}
		front=rear=NULL;
	}
	return 0;
}
