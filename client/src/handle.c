#include <stdio.h>
#include <stdlib.h>

#include "handle.h"
#include "java_rules_of_the_grammer.h"

// #define BASE_WIRE_HANDLE = 0x7E0000

struct handle *handle_list[256];
unsigned char sp = 0;

unsigned int new_handle_ncd(struct newclassdesc *ncd) {
    struct handle *h_ncd = malloc(sizeof(struct handle));
    h_ncd->type = REGIST_NCD;
    h_ncd->u.ncd = ncd;
    handle_list[sp] = h_ncd;
    return BASE_WIRE_HANDLE + sp++;
}

unsigned int new_handle_no(struct newobject *no) {
    struct handle *h_no = malloc(sizeof(struct handle));
    h_no->type = REGIST_NO;
    h_no->u.no = no;
    handle_list[sp] = h_no;
    return BASE_WIRE_HANDLE + sp++;
}

unsigned int new_handle_ns(struct newstring *ns) {
    printf("new_handle_ns\n");
    struct handle *h_ns = malloc(sizeof(struct handle));
    h_ns->type = REGIST_NS;
    h_ns->u.ns = ns;
    handle_list[sp] = h_ns;
    return BASE_WIRE_HANDLE + sp++;
}

struct handle *gethandle(unsigned int pos) {
    pos -= BASE_WIRE_HANDLE;
    return handle_list[pos];
}
