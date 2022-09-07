#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int main(){
	char str[100];
	char sendline[100];
	int sock_fd, comm_fd;
	struct sockaddr_in servaddr;	
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(22000);
	
	bind (sock_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	
	listen(sock_fd,10);
	comm_fd  = accept(sock_fd, (struct sockaddr*)NULL, NULL);
	
	
	while(1){
	
	
	
	bzero(str,100);
	bzero(sendline,100);
	recv(comm_fd, str, 100,0);
	printf("message is %s", str);
	fgets(sendline, 100, stdin);
	send(comm_fd, sendline, strlen(sendline), 0);
	close(comm_fd);
	
	}
	}
