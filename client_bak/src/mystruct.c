#include <stdio.h>

#include "mystruct.h"

// リストの前に追加
void add_byte_element_to_list(struct byte_struct b_buf, struct byte_list *b_list) {
    struct bytes_element *element = malloc(sizeof(struct bytes_element));
    element->bytes = b_buf;
    element->next = b_list->contents;
    b_list->contents = element;
    b_list->len += b_buf.len;
}

void add_byte_to_list(struct byte_struct b_buf, struct byte_list *b_list) {
    struct byte_struct buf;
    buf.contents = malloc(sizeof(char) * b_buf.len);
    memcpy(buf.contents, b_buf.contents, b_buf.len);
    buf.len = b_buf.len;
    add_byte_element_to_list(buf, b_list);
}

struct byte_list init_byte_list() {
    struct byte_list list;
    list.len = 0;
    list.contents = NULL;
    return list;
}

struct byte_struct list_to_bytes(struct byte_list b_list) {
    struct byte_struct bytes;
    bytes.len = b_list.len;
    bytes.contents = malloc(sizeof(char) * bytes.len);
    size_t length = 0;

    struct bytes_element *element = b_list.contents;
    while(element != NULL) {
        memcpy(&bytes.contents[b_list.len - length - element->bytes.len], element->bytes.contents, element->bytes.len);
        length += element->bytes.len;
        element = element->next;
    }
    return bytes;
}
