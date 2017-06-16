#ifndef PERSON_H
#define PERSON_H

#include "task.h"


#define PERSON_SERIAL_VERSION 0x1122334455667788

struct person {
  char *name;
};

struct data {
    struct send_data *sd;
};

struct send_field {
    struct send_data *sd;
    struct data d;
};

struct send_data {
    unsigned char type;
    char *name;
    unsigned long uid;
    unsigned char flag;
    struct send_field f;
    struct data d;
};

void convert_person(struct person *p, struct task *t);
char *return_str(char *str);
struct send_data create_send_person(struct person *p);

#endif
