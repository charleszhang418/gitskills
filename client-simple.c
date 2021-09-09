#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

const int BACKLOG = 10;
const int LISTENQ = 5000;
const int MAX_CONNECT = 20;

int main() {

    int sockfd;
    struct sockaddr_in serv_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket build failure");
        exit(1);
    }
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(1234);

    if (connect(sockfd, (struct sockraddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("connection failure");
        exit(1);
    }
    
    char bufS[100], bufR[100];

    while (1) {
        

        send(sockfd, bufS, strlen(bufS), 0);

        recv(sockfd, bufR, strlen(bufR), 0);

        memset(bufS, 0, 100);
        memset(bufR, 0, 100);

        close(sockfd);
    }
    return 0;
}