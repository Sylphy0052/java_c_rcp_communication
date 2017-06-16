#ifndef TASK_H
#define TASK_H

#include "java_rules_of_the_grammer.h"

// #define TASK_SERIAL_VERSION 0x8877665544332211

struct task {
    unsigned int v;
    char *str1;
    char *str2;
    unsigned char x;
    // void (*hello)(const struct task_t *, struct person_t);
};

void convert_task(struct stream *s, struct task *t);
void show_task(struct task *t);

#endif
