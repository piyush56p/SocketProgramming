#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>
int main()
{
    int sockfd;
    char *hello = "hello from client";
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;
    
    bzero(&servaddr,sizeof(servaddr));
    
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(22000);
    
    int n,len;
    len = sizeof(servaddr);
    while(1){
    fgets(sendline,100,stdin);
    sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
    
    recvfrom(sockfd,recvline,100,0,(struct sockaddr*)&servaddr,&len);
   
    printf("%s", recvline);
    
    //close(sockfd);
    }
    return 0;
}
