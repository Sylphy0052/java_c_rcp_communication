#include <stdio.h>

#include "handle.h"
#include "java_rules_of_the_grammer.h"

// #define BASE_WIRE_HANDLE = 0x7E0000

struct handle *handle_list[256];
unsigned char sp = 0;

unsigned int new_handle_ncd(struct newclassdesc *ncd) {
    struct handle *h_ncd = malloc(sizeof(struct handle));
    h_ncd->type = REGIST;
    h_ncd->u.ncd = ncd;
    handle_list[sp] = h_ncd;
    return BASE_WIRE_HANDLE + sp++;
}
