#include <stdlib.h>
#include <string.h>

#include "person.h"
#include "task.h"
#include "java_rules_of_the_grammer.h"

void convert_person(struct person *p, struct task *t) {
    size_t len = strlen(t->str1) + strlen(t->str2) + 1;
    p->name = malloc(sizeof(unsigned char) * len);
    memset(p->name, '\0', len);
    strcat(p->name, t->str1);
    strcat(p->name, t->str2);
}

char *return_str(char *str) {
    size_t len = strlen(str) + 1;
    char *name = malloc(sizeof(char) * len);
    strcpy(name, str);
    memset(&name[len], '\0', 1);
    return name;
}

struct send_data create_send_person(struct person *p) {
    struct send_data *sd = malloc(sizeof(struct send_data));
    sd->type = TC_OBJECT;
    sd->name = return_str("Person");
    sd->uid = PERSON_SERIAL_VERSION;
    sd->flag = SC_SERIALIZABLE;
    struct send_data *fd = malloc(sizeof(struct send_data));
    sd->f.d.sd = fd;
    fd->type = TC_STRING;
    fd->name = return_str("Ljava/lang/String;");
    struct send_data *f = malloc(sizeof(struct send_data));
    sd->f.sd = f;
    f->type = 'L';
    f->name = return_str("name");
    struct send_data *d = malloc(sizeof(struct send_data));
    sd->d.sd = d;
    d->type = TC_STRING;
    d->name = return_str(p->name);
    return *sd;
}
