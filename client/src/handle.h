#ifndef HANDLE_H
#define HANDLE_H

#include "java_rules_of_the_grammer.h"

#define REGIST 0x00

struct handle {
    unsigned char type;
    union {
        struct newclassdesc *ncd;
    } u;
};

unsigned int new_handle_ncd(struct newclassdesc *ncd);

#endif
