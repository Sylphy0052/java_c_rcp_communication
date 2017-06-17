#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "mysocket.h"
#include "mystruct.h"
#include "task.h"
#include "person.h"
#include "serialize.h"

#define PORT 4000

int connect_socket() {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    const int sock = socket(AF_INET, SOCK_STREAM, 0);
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    printf("Connect to Server!\n");
    return sock;
}

struct byte_struct send_and_receive_socket(int sock, char *order) {
    size_t order_length = strlen(order);
    char *command = malloc(sizeof(char) * order_length);
    memset(command, '\0', order_length);
    strcat(command, order);
    size_t command_length = strlen(command);

    send(sock, command, command_length, 0);
    free(command);
    struct byte_list b_list = init_byte_list();
    b_list.contents = NULL;
    size_t sum = 0;
    int len;
    unsigned char *buf = malloc(sizeof(unsigned char) * 64);
    printf("recv\n");
    while((len = recv(sock, buf, sizeof(buf), 0)) != 0) {
        if(len < 0) {
            free(buf);
            printf("recv error!\n");
            exit(0);
        }
        struct byte_struct b_buf;
        b_buf.contents = buf;
        b_buf.len = len;
        add_byte_to_list(b_buf, &b_list);
        sum += len;
    }
    free(buf);
    close(sock);
    struct byte_struct bytes = list_to_bytes(b_list);
    return bytes;
}

void send_socket(char *order, char *method, struct byte_struct bytes) {
    size_t len = strlen(order) + strlen(method);
    char *command = malloc(sizeof(char) * len);
    memset(command, '\0', len);
    strcat(command, order);
    strcat(command, " ");
    strcat(command, method);
    struct byte_struct bytes_len = bytes_from_int(bytes.len);

    int sock = connect_socket();
    send(sock, command, len, 0);
    send(sock, bytes_len.contents, bytes_len.len, 0);
    send(sock, bytes.contents, bytes.len, 0);
    free(command);
    close(sock);
}

void send_person(char *order, struct person *p) {
    struct send_data sd = create_send_person(p);
    struct byte_struct bytes = serialize(sd);
    send_socket(order, "hello\n ", bytes);
}
