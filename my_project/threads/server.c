#include"header.h"
void *thf(void *);
int main()
{
int count = 0;
	system("clear");
	pthread_t th;
	pthread_attr_t *attr;
	attr = (pthread_attr_t *)malloc(sizeof(pthread_attr_t));
	int ret,ret1;
	struct database d;
	int server_fd;
	printf("<-----------------Server Program Started---------------------->\n");
	ret = mkfifo(SERVER_FIFO,0777);
	if(ret!=0)
	{
		printf("SERVER_FIFO  Creation Failed= %d\n",ret);
		exit(-1);
	}
	printf("Return Value SERVER_FIFO = %d\n",ret);
	server_fd = open(SERVER_FIFO,O_RDONLY);
	if(server_fd == -1)
	{
		fprintf(stderr,"Server Fifo Failure\n");
		exit(-1);
	}
	while(1)
	{
			do
			{
				printf("reading from %dth client\n",count);
				ret1 = read(server_fd,&d,sizeof(d));
				if(ret1 > 0)
				{

					printf("\t\t\tCOUNT = %d\n",++count);
					if(pthread_attr_init(attr))
					{
						printf("failed pthread_attr_init:");
					}
					if(pthread_attr_setdetachstate(attr,PTHREAD_CREATE_DETACHED))
					{
						printf("failed pthread_attr_setdetachstate:");
					}
					if(pthread_create(&th,0,&thf,(void *)&d))
						printf("failed pthread_create............");
					pthread_attr_destroy(attr);
				}
				else 
					printf("ret1 = %d\n",ret1);
			
		}while(ret1 > 0);
}
	close(server_fd);
	unlink(SERVER_FIFO);
	printf("<-------------------Server Program Ended------------------------->\n");
	return 0;
}
void *thf(void * da)
{
	int client_fd,buff1[1],val1,val2,ret2;
	char client_fifo[256],op;
	struct database *d;
	d = (struct database *) da;
	val1 = d->data[1];
	val2 = d->data[2];	
	op = d->data[0];
	sprintf(client_fifo,CLIENT_FIFO,d->client_pid);
	switch(op)
	{
		case '+':
			{
				buff1[0] = val1 + val2;
				break;
			}
		case '*':
			{
				buff1[0] = val1 * val2;
				break;
			}
		case '-':
			{
				buff1[0] = val1 - val2;
				break;
			}
		case '/':
			{
				buff1[0] = val1 / val2;
				break;
			}
		default:
			{
				printf("operator unknown\n");
			}
	}
				printf("SERVER: Addition Result at Server%d %c %d = %d\n",val1,op,val2,buff1[0]);
				client_fd = open(client_fifo,O_WRONLY);
				if(client_fd != -1)
				{
					ret2 = write(client_fd,buff1,sizeof(int));
					close(client_fd);
				}
}
