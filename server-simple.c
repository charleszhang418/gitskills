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
#include <sys/select.h>
#include <sys/time.h>

#define MAX_CONNECT 20

int main() {
    
    int sockfd, tempfd, maxfdp, selc, client_info[20];
    struct sockaddr_in serv_addr, clnt_addr;
    fd_set readset;
    char buf[100];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("wrong socket");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(1234);

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind failure");
        exit(1);
    }

    if (listen(sockfd, 10) == -1) {
        perror("listen failure");
        exit(1);
    }

    while(1) {
        if ((selc = select(maxfdp, &readset, NULL, NULL, NULL)) == -1) {
            perror("selection failure");
            exit(1);
        }


        if ((tempfd = accpet(sockfd, (struct sockaddr*)&clnt_addr, sizeof(clnt_addr))) == -1) {
            perror("accept failure");
            exit(1);
        }

        for (int i = 0; i < MAX_CONNECT; i++) {
            tempfd = client_info[i];
            selc = read(tempfd, buf, sizeof(buf));
            if (selc == -1) {
                selc = write(tempfd, buf, strlen(buf));
            } else {
                close(tempfd);
                client_info[i] = 0;
            }
        }
    }

    close(sockfd);
    
}