#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<sys/un.h>
int main()
{
	char ch[100];
	int server_socket_fd,client_socket_fd;
	int server_len,client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
	unlink("server_socket");
	server_socket_fd = socket(AF_UNIX,SOCK_STREAM,0);
	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "server_socket");
	server_len = sizeof(server_address);
	//printf("server_len = %d\n",server_len);
	bind(server_socket_fd,(struct sockaddr *)&server_address,server_len);
	listen(server_socket_fd,5);
	//printf("server waiting\n");
	client_len = sizeof(client_address);
	client_socket_fd = accept(server_socket_fd,(struct sockaddr *)&client_address,&client_len);
	while(1)
	{
		printf("Sever Waiting : \n");
		read(client_socket_fd,ch,100);
		printf("server:  %s\n",ch);
		gets(ch);
		//if(strncmp(ch,"bye",3)==0)
		//exit(0);
		write(client_socket_fd,ch,100);
		memset(ch,'\0',strlen(ch));
	}
}
