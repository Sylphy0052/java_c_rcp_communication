#ifndef MYSOCKET_H
#define MYSOCKET_H

#include "person.h"

int connect_socket();
struct byte_struct send_and_receive_socket(int sock, char *order);
void send_person(char *order, struct person *p);

#endif
