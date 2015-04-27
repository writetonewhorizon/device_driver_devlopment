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
				printf("reading from %dth client\n",++count);
				ret1 = read(server_fd,&d,sizeof(d));
				if(ret1 > 0)
				{

					printf("\t\t\tCOUNT = %d\n",count);
					if(pthread_attr_init(attr))
					{
						printf("failed pthread_attr_init:");
					}
					if(pthread_attr_setdetachstate(attr,PTHREAD_CREATE_DETACHED))
					{
						printf("failed pthread_attr_setdetachstate:");
					}
					pthread_create(&th,0,&thf,(void *)&d);
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
	int client_fd,j,pid3,ret2;
	char conwrite1[2],value1[2],value2[2],value3[2];
	int ret,buff[4],buff1[2],pro[2];
	char client_fifo[256];
	struct database *d;
	d = (struct database *) da;
	ret = pipe(pro);
	sprintf(client_fifo,CLIENT_FIFO,d->client_pid);
	j=0;
	printf("value 1 = %d\n",d->data[1]);
	sprintf(value2,"%d",d->data[1]);
	printf("value 1 = %c\n",value2);
	sprintf(value3,"%d",d->data[2]);	
	value1[0] = d->data[0];
	ret = pipe(pro);
	if(ret == 0)
	{
	//				printf("SERVER: Pipe2 from Server To Process created\n");
	//				printf("SERVER: Pipe2 Read FD = %d & Write FD = %d\n",pro[0],pro[1]);
	sprintf(conwrite1,"%d",pro[1]);
	switch(value1[0])
	{
		case '+':
			pid3 = fork();
			if(pid3 < 0)
			{
				printf("SERVER: Fork for Processing CLIENT1  Failed");
				exit(-1);
			}
			else if(pid3 == 0)
				execl("./addition","addition",conwrite1,value2,value3,NULL);
			else if(pid3>0)
			{
				read(pro[0],buff1,sizeof(int));
				printf("SERVER: Addition Result at Server = %d\n",buff1[0]);
				client_fd = open(client_fifo,O_WRONLY);
				if(client_fd != -1)
				{
					ret2 = write(client_fd,buff1,sizeof(int));
					close(client_fd);
			//		count++;
				}
				if(pid3>0)
				{
					int stat_val1;
					pid_t child_pid1;
					child_pid1 = waitpid(pid3,&stat_val1,0);
					if(WIFEXITED(stat_val1))
					{
						printf("Addition child Exited Normally Pid = %d\n",child_pid1);
					}
					else
					{
						printf("Addition child Exited AbNormaly Pid = %d\n",child_pid1);
					}
				}
			}
			memset(buff,'\0',sizeof(buff));
			break;
		case '-':
			pid3 = fork();
			if(pid3 < 0)
			{
				printf("SERVER: Fork for Processing CLIENT1  Failed");
				exit(-1);
			}
			else if(pid3 == 0)
				execl("./subtract","subtract",conwrite1,value2,value3,NULL);
			else if(pid3>0)
			{
				read(pro[0],buff1,sizeof(int));
				printf("SERVER: Subtract Result at Server = %d\n",buff1[0]);
				client_fd = open(client_fifo,O_WRONLY);
				if(client_fd != -1)
				{
					ret2 = write(client_fd,buff1,sizeof(int));
					close(client_fd);
			//		count++;
				}
				if(pid3>0)
				{
					int stat_val1;
					pid_t child_pid1;
					child_pid1 = waitpid(pid3,&stat_val1,0);
					if(WIFEXITED(stat_val1))
					{
						printf("Subtract child Exited Normaly Pid = %d\n",child_pid1);
					}
					else
					{
						printf("Subtract child Exited AbNormaly Pid = %d\n",child_pid1);
					}
				}
			}
			memset(buff,'\0',sizeof(buff));
			break;
		case '*':
			pid3 = fork();
			if(pid3 < 0)
			{
				printf("SERVER: Fork for Processing CLIENT1  Failed");
				exit(-1);
			}
			else if(pid3 == 0)
			{
				execl("./multiply","multiply",conwrite1,value2,value3,NULL);
			}
			else if(pid3>0)
			{
				read(pro[0],buff1,sizeof(int));
				printf("SERVER: Multiply Result at Server = %d\n",buff1[0]);
				client_fd = open(client_fifo,O_WRONLY);
				if(client_fd != -1)
				{
					ret2 = write(client_fd,buff1,sizeof(int));
					close(client_fd);
			//		count++;
				}
				if(pid3>0)
				{	
					int stat_val1;
					pid_t child_pid1;
					child_pid1 = waitpid(pid3,&stat_val1,0);
					if(WIFEXITED(stat_val1))
					{
						printf("Multiply child Exited Normally Pid = %d\n",child_pid1);
					}
					else
					{
						printf("Multiply child Exited AbNormaly Pid = %d\n",child_pid1);
					}
				}
			}
	}
	}//free(d);
}
