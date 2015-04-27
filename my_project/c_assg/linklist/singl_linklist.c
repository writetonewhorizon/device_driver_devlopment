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
	int choice,n,i,m,pos;
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
		printf("10.to chech circulerity\n"); 
		printf("11.exit\n");
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
				printf("enter the element at the begining :\n");
				scanf("%d",&m);
				add_at_beg(m);
				break;
			case 3:
				display();
				break;

			case 4:
				printf("enter the position at which you want to add the node:\n");
				scanf("%d",&pos);
				printf("enter the data :\n"); 
				scanf("%d",&m);
				add_after(m,pos);
				break;
			case 5:
				printf("enter the position of node that you want to delete:\n");
				scanf("%d",&pos);
				delete(pos);
				break;
			case 6:
				printf("enter the itam you want to serch:\n"); 
				scanf("%d",&m);
				serch(m);
				break;
			case 7:
				printf("reverse linklist is :\n"); 
				reverse();
				break;
			case 8:
				printf("sorting of linklist\n"); 
				sort_linklist();
				break;
			case 9:
				remove_duplicate();
				break;
			case 10:
				circuler_linklist();
				break;
			case 11:
				exit(0);
				break;
			default :
				printf("entered wronge choice");
				break;

		}
			
	}
	return 0;
}
create_list(int data)
{
	struct node *tamp,*local;
	tamp=malloc(sizeof(struct node));
	tamp->info=data;
	printf("temp->info = %d\n",tamp->info); 
	tamp->link=NULL;
	if(start==NULL)
	{
		printf("starting linllist\n");
		start=tamp;
		printf("start=%p\n",&start); 
		printf("tamp=%p\n",&tamp); 
	}
	else
	{
		printf("in else part\n"); 
		local=start;
		while(local->link!=NULL)
		{
			local=local->link;
		}
			local->link=tamp;
	}

}
add_at_beg(int data)
{
	struct node *tamp;
	tamp=malloc(sizeof(struct node));
	tamp->info=data;
	tamp->link=start;
	start=tamp; 
	return 0;
}
display()
{
	struct node *local;
	if(start==NULL)
	{
		printf("list is empty:\n");
		return 1;
	}
		local=start;
		printf("list is :\n");
		while(local!=NULL)
		{
			printf("%d\n",local->info);
			local=local->link;
		}
		printf("\n"); 
		return 0;
}
add_after(int data,int pos)
{
	struct node *local,*tamp;
	int i;
	if(start==NULL)
	{
		printf("node are less than position:\n"); 
	}
	else
	{
		local=start;
		for(i=0;i<pos;i++)
		{
			local=local->link;
		}
		tamp=malloc(sizeof(struct node));
		tamp->info=data;
		tamp->link=local->link;
		local->link=tamp;

	}
return 0;
}
delete(int pos)
{
	struct node *local,*tamp;
	int i;
	if(start==NULL)
	{
		printf("list is empty so cannot delet it:\n");
		return 1;
	}
	else
	{
		tamp=local=start;
		for(i=1;i<pos-1;i++)
		{
			local=local->link;
		}
		for(i=1;i<=pos;i++)
		{
			tamp=tamp->link;
		}
		local->link=tamp->link;
	}
}
serch(int data)
{
	struct node *local;
	int pos=0;
	if(start==NULL)
	{
		printf("list is empty:\n");
		return 1;
	}
	else
	{
		local=start;
		while(local->link!=NULL)
		{
			if(local->info==data)
			{
				printf("data is found is %d and its position is %d\n",local->info,pos); 
				break;
			}
			local=local->link;
			pos++;
		}
		if(local->link==NULL)
		{
			printf("data is not in the list\n"); 
		}

	}
	return 0;
}
reverse()
{
	struct node *local,*tamp,*tamp1;
	if(start== NULL)
	{
		printf("reverse is not possible\n");
		return 1;
	}
	local=start;
	tamp=local->link;
	tamp1=tamp->link;
	local->link=NULL;
	tamp->link=local;
	while(tamp1!=NULL)
	{
		local=tamp;
		tamp=tamp1;
		tamp1=tamp1->link;
		tamp->link=local;
	}
	start =tamp;
return 0;
}
sort_linklist()
{
	struct node *local,*tamp;
	int num,i;
	int count=0;
	int cnt=0;
	local=start;
	printf("%p\n",&local); 
	tamp=local->link;
	while(local!=NULL)
	{
		local=local->link;
		count++;
	}
	printf("count=%d\n",count);
	printf("%p\n",&local); 
	local=start;
	printf("%p\n",&local); 
	for(i=0;i<count-1;i++)
	{
		while(local->link!=NULL)
		{
			if(tamp->info < local->info)
			{
				num=local->info;
				local->info=tamp->info;
				tamp->info=num;
				printf("local->info=%d\n",local->info);
			 	printf("tamp->info=%d\n",tamp->info);	
			}
			local=local->link;
			tamp=tamp->link;
			cnt++;
		}
		local=start;
		tamp=local->link;
		printf("cnt=%d\n",cnt); 
	}
	return 0;
}	
remove_duplicate()
{
	struct node *local,*tamp,*tamp1;
	local=start;
	tamp=local->link;
	while(local->link!=NULL)
	{
		if(tamp->info==local->info)
		{
			tamp1=tamp->link;
			local->link=tamp->link;
			tamp=tamp1;
		}
		else
		{
			local=local->link;
			tamp=tamp->link;
		}

	}
	return 0;
}
circuler_linklist()
{
	struct node *local,*tamp;
	int count=0;
	local=start;
	printf("local=%p\n",&local); 
	tamp=local->link;
	printf("tamp=%p\n",&tamp); 
	while(tamp!=NULL)
	{
		if(local==tamp)
		{
			printf("%p,%p\n",&local,&tamp); 
			printf("linklist is circuler\n");
			return 1;
		}
			local=local->link;
			printf("local=%p\n",&local); 
			tamp=tamp->link;
			printf("tamp=%p\n",&tamp); 
			count++;
			printf("count=%d\n",count); 
	}
	printf("linklist is not circuler\n"); 
	return 0;
}
