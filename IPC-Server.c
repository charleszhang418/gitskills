#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 0
#define TEMPPORT 0

void main() {
    int sockfd, socktemp, bindfd, sendfd;
    struct sockaddr_in serverAddr, tempAddr, clientAddr;
    socklen_t addr_size;
    char buf[1024];

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("Socket build failure");
        exit(1);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_family = AF_UNIX;

    if ((bindfd = bind(socktemp, (struct sockaddr*)&socktemp, sizeof(socktemp))) == -1) {
        perror("Bind failure");
        exit(1);
    }

    tempAddr.sin_port = TEMPPORT;

    listen(sockfd, 10);

    addr_sizeof(clientAddr);
    
    if ((socktemp = accept(sockfd, (struct sockaddr*)&tempAddr, sizeof(socktemp))) == -1) {
        perror("Accept failure");
        exit(1);
    }

    while(1) {
        memset(buf, 0, sizeof(buf));
        fgets(buf, 1024, stdin);
        if ((sendfd = send(socktemp, buf, strlen(buf), 0)) == -1) {
            perror("Send failure");
            exit(1);
        }

        if (!strcmp(buf, "disconnect\n")) {
            break;
        }
    }
    close(sockfd);
    exit(0);
}