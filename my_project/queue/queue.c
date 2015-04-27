#include<stdio.h>
#include<stdlib.h>
#define sige 10
void create_queue();
//void enqueue();
//void dequeue();
//void delete_queue();
//void display_queue();
//void reinitiliagation_queue();
int queue[sige],rear=-1,front=-1,item;
int main()
{
int choice;
do
	{
	
		printf("___start manu___\n");
		printf("create queue\n");
		printf("enqueue\n");
		printf("dequeue\n");
		printf("delete queue\n");
		printf("display queue\n");
		printf("reinitiliagation queue\n");
		printf("exit manu\n");
		printf("enter your choice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				create_queue();
				break;
		/*	case 2:
				enqueue();
				break;
			case 3:
				dequeue();
				break;
			case 4:
				delete_queue();
				break;
			case 5:
				display_queue();
				break;
			case 6:
				reinitiliagation_queue();
				break;*/
			case 7:
				exit(0);
			default:
				printf("invalid choice. please try again...\n");
		}
	}while(1);	
}
void create_queue()
{

	if(rear == sige-1)
	{
		printf("queue is full.");
	}
	else
	{
		printf("enter item: ");
		scanf("%d", &item);
	if(rear ==-1 && front ==-1)
	{
		rear = 0;
		front = 0;
	}
	else
	{
	rear++;
	queue[rear] = item;
	printf("item inserted %d", item);

	}	
}	
}
