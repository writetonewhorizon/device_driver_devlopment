#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int sockfd,len,result;
	struct sockaddr_in address;
	char ch[100],ch1[100];
	printf("this is client : \n");
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	printf("sockfd = %d\n",sockfd);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr = inet_addr("198.168.0.3");
	address.sin_port =2000;
	len = sizeof(struct sockaddr_in);
	printf("%d\n",len);
	result = connect(sockfd,(struct sockaddr *)&address,8);
//	result=connect(sockfd,(struct sockaddr *)&address,len);
	printf("connect return is %d\n",result);
	while(1)
	{
		fgets(ch,100,stdin);
		result=write(sockfd,ch,100);
		printf("writen data is %d\n ",result);
		memset(ch,'\0',100);
		memset(ch1,'\0',100);
		read(sockfd,ch1,100);
		printf("%s\n",ch);
	}
//	close(sockfd);
}
