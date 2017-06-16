#include <string.h>

#include "java_rules_of_the_grammer.h"
#include "task.h"

void convert_task(struct stream *s, struct task *t) {
    // struct fielddesc *fd = s->c.c.u.o.u.no.cd.u.ncd.cdi.f.fd;
    struct classdata *cds = s->c->c.u.o->u.no.cds;
    t->v = cds->u.i;
    cds = cds->next;
    t->x = cds->u.b;
    cds = cds->next;
    t->str1 = cds->u.o->u.ns.utf;
    cds = cds->next;
    t->str2 = cds->u.o->u.ns.utf;

    // while(fd != NULL && cds != NULL) {
        // printf("name : %s\n", fd->u.pd.fn.name);
        // if(strcmp("v", fd->u.pd.fn.name) == 0) {
        //     printf("A\n");
        //     t.v = cds->u.i;
        // } else if (strstr(fd->u.pd.fn.name, "x") != NULL) {
        //     printf("B\n");
        //     t.x = cds->u.b;
        // } else if (strstr(fd->u.pd.fn.name, "str1") != NULL) {
        //     printf("C\n");
        //     t.str1 = cds->u.o->u.ns.utf;
        // } else if (strstr(fd->u.pd.fn.name, "str2") != NULL) {
        //     printf("D\n");
        //     t.str2 = cds->u.o->u.ns.utf;
        // }
        // printf("Integer : 0x%x\n", cds->u.i);
        // printf("Byte : 0x%x\n", cds->u.i);
        // fd = fd->next;
        // cds = cds->next;
    // }
}

void show_task(struct task *t) {
    printf("===show task===\n");
    printf("v: 0x%x\n", t->v);
    printf("x: %d\n", t->x);
    printf("str1: %s\n", t->str1);
    printf("str2: %s\n", t->str2);
}
