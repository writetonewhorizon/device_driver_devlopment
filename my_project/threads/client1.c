#include"header.h"

int main()
{
	int ret,i,buff[1],server_fd,client_fd;
	char client_fifo[256];
	struct database c;
	c.data[0] = '+';
	c.data[1] = 5;
	c.data[2] = 4;
	c.client_pid = getpid();
	printf("<---------------Program Client1 Started----------------->\n");
	//printf("CLIENT1: Data to be Written to Server : Sign = %d, Val1 = %d, Val2 = %d, C1PID: = %d\n",c.data[0],c.data[1],c.data[2],c.client_pid);	
	server_fd = open(SERVER_FIFO,O_WRONLY);
	if(server_fd == -1)
	{
		fprintf(stderr,"Sorry No Server Found\n");
		exit(-1);
	}
	sprintf(client_fifo,CLIENT_FIFO,c.client_pid);
	if(mkfifo(client_fifo, 0777) == -1)
	{
		fprintf(stderr,"Sorry,can't make %s Fifo\n",client_fifo);
		exit(-1);
	}
	ret = write(server_fd,&c,sizeof(c));
//	printf("CLIENT1: %d Bytes Written to Server\n",ret);
	client_fd = open(client_fifo,O_RDONLY);
	//sleep(1);
	if(client_fd != -1)
	{
		read(client_fd,buff,sizeof(int));
	}
	printf("\t\t_____CLIENT1:4 + 5 = %d_____\n",buff[0]);
	close(client_fd);
	close(server_fd);
	unlink(client_fifo);
	
	printf("<---------------Program Client1 Ended--------------------->\n");
	exit(0);
}
