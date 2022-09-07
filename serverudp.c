#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
int main(){
    char sendline[100];
    char revline[100];
    
    int sock_fd;
    int n;
    struct sockaddr_in servaddr, clientaddr;
    
    bzero(&servaddr, sizeof(servaddr));
    bzero(&clientaddr, sizeof(clientaddr));
    
    sock_fd = socket(AF_INET,SOCK_DGRAM,0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons (22000);
    
    bind(sock_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    int len;
    len = sizeof(clientaddr);
    while(1){
    recvfrom(sock_fd, revline,100,0, (struct sockaddr*)&clientaddr, &len);
    
    
    printf("%s", revline);
    fgets(sendline,100,stdin);
    sendto(sock_fd,sendline, strlen(sendline), 0, (struct sockaddr*) &clientaddr, sizeof(clientaddr));
    }
    return 0;
}
