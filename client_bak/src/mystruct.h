#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <stdio.h>

struct byte_struct {
    unsigned char *contents;
    size_t len;
};

struct bytes_element {
    struct byte_struct bytes;
    struct bytes_element *next;
};

struct byte_list {
    struct bytes_element *contents;
    size_t len;
};

void add_byte_element_to_list(struct byte_struct b_buf, struct byte_list *b_list);
void add_byte_to_list(struct byte_struct b_buf, struct byte_list *b_list);
struct byte_list init_byte_list();
struct byte_struct list_to_bytes(struct byte_list b_list);


#endif
