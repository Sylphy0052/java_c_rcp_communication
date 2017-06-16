#ifndef HANDLE_H
#define HANDLE_H

#include "java_rules_of_the_grammer.h"

#define REGIST_NCD 0x00
#define REGIST_NO 0x01
#define REGIST_NS 0x02

struct handle {
    unsigned char type;
    union {
        struct newclassdesc *ncd;
        struct newobject *no;
        struct newstring *ns;
    } u;
};

unsigned int new_handle_ncd(struct newclassdesc *ncd);
unsigned int new_handle_no(struct newobject *no);
unsigned int new_handle_ns(struct newstring *ns);
struct handle *gethandle(unsigned int pos);
#endif
