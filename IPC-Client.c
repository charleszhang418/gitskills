#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 0
#define CLIENTPORT 0

void main() {
    int ClientSocket;
    struct sockaddr_in clientAddr;
    char buf[1024];

    if ((ClientSocket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("Socket build failure");
        exit(1);
    }

    memset(&clientAddr, 0, sizeof(clientAddr));

    clientAddr.sin_family = AF_UNIX;
    clientAddr.sin_port = CLIENTPORT;
    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((connect(ClientSocket, (struct sockaddr*)&clientAddr, sizeof(clientAddr))) == -1) {
        perror("Connection error");
        exit(1);
    }

    while(1) {
        recv(ClientSocket, buf, 1024, 0);
        if (!strcmp(buf, "disconnect\n")) {
            break;
        }
        memset(buf, 0, sizeof(buf));
    }
    close(ClientSocket);
    exit(0);
}