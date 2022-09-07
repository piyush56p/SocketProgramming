#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
int main(char *argc,char **argv)
{
	char sendline[100];
	char recvline[100];
	int sockfd,n;
	struct sockaddr_in servaddr;
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(22000);
	inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
	
	connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	while(1)
	{
		bzero(sendline,100);
		bzero(recvline,100);
		fgets(sendline,100,stdin);
		send(sockfd,sendline,strlen(sendline),0);
		recv(sockfd,recvline,100,0);
		printf("%s",recvline);
		}
		}
