#include<stdio.h>
#include<stdlib.h>
#include<sys/un.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
int main()
{
	int socket_fd;
	int length,result;
	char ch[100];
	struct sockaddr_un server_address;
	socket_fd=socket(AF_UNIX,SOCK_STREAM,0);      /*socket created --------*/
//	printf("socket_fd %d\n",socket_fd);
	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path,"server_socket");
	length=sizeof(server_address);
	result=connect(socket_fd,(struct sockaddr *)&server_address,length);
//	printf("result %d\n",result);
	printf("start chat now :\n");
	while(1)
	{
		gets(ch);
		if(strncmp(ch,"bye",3)== 0)
		exit(0);
		write(socket_fd,ch,100);
		read(socket_fd,ch,100);
		printf("client :  %s\n",ch);
	}
	close(socket_fd);
}

