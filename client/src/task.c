
#include "java_rules_of_the_grammer.h"
#include "task.h"

struct task convert_task(struct stream s) {
    struct task t;
    struct fielddesc *fd = s.c.c.u.o.u.no.cd.u.ncd.cdi.f.fd;
    struct classdata *cds = &s.c.c.u.o.u.no.cds;
    while(fd != NULL && cds != NULL) {
        if(strcmp("v", fd->u.pd.fn.name) == 0) {
            t.v = cds->u.i;
        } else if (strcmp("x", fd->u.pd.fn.name) == 0) {
            t.x = cds->u.b;
        } else if (strcmp("str1", fd->u.pd.fn.name) == 0) {
            t.str1 = cds->u.o->u.ns.utf;
        } else if (strcmp("str2", fd->u.pd.fn.name) == 0) {
            t.str2 = cds->u.o->u.ns.utf;
        }
        fd = fd->next;
        cds = cds->next;
    }
    return t;
}

void show_task(struct task t) {
    printf("t.v: 0x%x\n", t.v);
    printf("t.x: %d\n", t.x);
    printf("t.str1: %s\n", t.str1);
    printf("t.str2: %s\n", t.str2);
}
