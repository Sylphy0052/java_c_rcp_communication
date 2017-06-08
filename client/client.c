#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "src/parser.h"

#define PORT 4444

int main(int argc, char const *argv[]) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    const int sock = socket(AF_INET, SOCK_STREAM, 0);
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    const char* message = "send message\n";
    send(sock, message, strlen(message), 0);

    int len;
    unsigned char *buf = malloc(sizeof(unsigned char) * 64);
    unsigned char *byte_list = malloc(sizeof(unsigned char) * 64);
    int list_length = 0;
    while((len = recv(sock,buf, sizeof(buf), 0)) != 0) {
        if(len < 0) {
            printf("recv error!\n");
            return 0;
        }
        int i;
        for(i = 0; i < len * sizeof(unsigned char); i++) {
            byte_list[list_length + i] = buf[i];
        }
        list_length += len * sizeof(unsigned char);
    }
    free(buf);
    parse(byte_list, list_length);

    close(sock);
    return 0;
}
