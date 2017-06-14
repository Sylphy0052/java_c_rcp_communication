#ifndef TASK_H
#define TASK_H

// #define TASK_SERIAL_VERSION 0x8877665544332211

struct task {
    int v;
    char *str1;
    char *str2;
    char x;
    // void (*hello)(const struct task_t *, struct person_t);
};

struct task convert_task(struct stream s);

#endif
