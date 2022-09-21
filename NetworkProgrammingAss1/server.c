#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

char webpage[] = 
"HTTP/1.1 200 Ok\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html>\r\n"
"<html><head><title>Test Title</title>\r\n"
"<body><img src='test.png' width = '50%'/>"
"<p> My name is Piyush Sharma </p>"
"<p> My rollno is 102003417 </p>"
"<p> My group is COE16 </p></body>"
"</html>";

int main(int argc, char *argv[]){
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_len = sizeof(client_addr);
    int fd_server, fd_client;
    /* Storing the contents sent by the browser (a request) */
    char buf[2048];
    int fdimg;
    int on = 1;

    fd_server = socket(AF_INET, SOCK_STREAM, 0);
    if(fd_server < 0){
        perror("socket");
        exit(1);
    }

    setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if(bind(fd_server, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
        perror("bind");
        close(fd_server);
        exit(1);
    }

    if(listen(fd_server, 10) == -1){
        perror("listen");
        close(fd_server);
        exit(1);
    }

    while(1){
        fd_client = accept(fd_server, (struct sockaddr *) &client_addr, &sin_len);

        if(fd_client == -1){
            perror("Connection failed...\n");
            continue;
        }

        printf("Got client connection...\n");

        if(!fork()){

            /* Child process */

            /* Close this as the client no longer needs it */
            close(fd_server);
            memset(buf, 0, 2048);
            read(fd_client, buf, 2047); /* 2047 because of null char? */

            /* Print the request on the console */
            printf("%s\n", buf);

            if(!strncmp(buf, "GET /test.png", 13)){
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                fdimg = open("test.png", O_RDONLY);
                int sent = sendfile(fd_client, fdimg, NULL, 10000);
                printf("sent: %d", sent);
                close(fdimg);
            }
            else{
                write(fd_client, webpage, sizeof(webpage) - 1);
            }

            close(fd_client);
            printf("closing connection...\n");
            exit(0);
        }

        /* Parent process */
        close(fd_client);


    }   


    return 0;

}
