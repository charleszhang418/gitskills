#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    struct sockaddr_in serv_addr;
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(0001);
    
    char bufS[100] = {0}, bufR[100] = {0};

    while (1) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        connect(sock, (struct sockraddr*)&serv_addr, sizeof(serv_addr));

        send(sock, bufS, strlen(bufS), 0);

        recv(sock, bufR, strlen(bufR), 0);

        memset(bufS, 0, 100);
        memset(bufR, 0, 100);

        close(sock);
    }
    return 0;
}