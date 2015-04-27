#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int server_sockfd,client_sockfd,result;
	char ch[10];
	int wc,rc;
	int server_len,client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	server_sockfd=socket(AF_INET,SOCK_STREAM,0);
//	printf("sockfd is  %d\n",server_sockfd);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("192.168.0.12");
	server_address.sin_port = htons(1032);
	server_len = sizeof(server_address);
	printf("server_len = %d\n",server_len);
	result=bind(server_sockfd,(const struct sockaddr *)&server_address,server_len);
//	printf("bind's return value is %d\n",result);
	result=listen(server_sockfd,5);
//	printf("listen's return value is %d\n",result);
	printf("server is ready to chat : \n");
		client_len = sizeof(client_address);
		//printf("len = %d\n",client_len);
		printf("server waiting : \n");
		client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
	while(1)
	{
		printf("accept's return value is %d\n",client_sockfd);
		rc = read(client_sockfd,ch,10);
		printf("data: %d  %s\n",rc,ch);
		fgets(ch,10,stdin);
		wc = write(client_sockfd,ch,10);
		printf("wc = %d\n",wc);
		memset(ch,'\0',10);
	}
		close(client_sockfd);
}
