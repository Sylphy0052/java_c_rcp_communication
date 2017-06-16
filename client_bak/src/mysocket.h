#ifndef MYSOCKET_H
#define MYSOCKET_H

int connect_socket();
struct byte_struct send_and_receive_socket(int sock, char *order);

#endif
