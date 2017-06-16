#include "person.h"
#include "mystruct.h"

struct byte_struct bytes_from_char(unsigned char c) {
  struct byte_struct bytes;
  bytes.len = 1;
  bytes.contents = malloc(sizeof(char) * bytes.len);
  bytes.contents[0] = c;
  return bytes;
}

struct byte_struct bytes_from_short(unsigned short s) {
  struct byte_struct bytes;
  bytes.len = 2;
  bytes.contents = malloc(sizeof(char) * bytes.len);
  for (size_t i = 1; i <= bytes.len; i++) {
    bytes.contents[bytes.len - i] = (unsigned char)s;
    s >>= BYTE;
  }
  return bytes;
}

struct byte_struct bytes_from_int(unsigned int integer) {
  struct byte_struct bytes;
  bytes.len = 4;
  bytes.contents = malloc(sizeof(char) * bytes.len);
  for (size_t i = 1; i <= bytes.len; i++) {
    bytes.contents[bytes.len - i] = (unsigned char)integer;
    integer >>= BYTE;
  }
  return bytes;
}

struct byte_struct bytes_from_long(unsigned long l) {
  struct byte_struct bytes;
  bytes.len = 8;
  bytes.contents = malloc(sizeof(char) * bytes.len);
  for (size_t i = 1; i <= bytes.len; i++) {
    bytes.contents[bytes.len - i] = (unsigned char)l;
    l >>= BYTE;
  }
  return bytes;
}

struct byte_struct bytes_from_string(char *str) {
  struct byte_struct bytes;
  size_t slen = strlen(str);
  bytes.len = slen + 2;
  bytes.contents = malloc(sizeof(char) * bytes.len);
  memcpy(&bytes.contents[2], str, slen);
  for (size_t i = 1; i <= 2; i++) {
    bytes.contents[2 - i] = (unsigned char)slen;
    slen >>= BYTE;
  }
  return bytes;
}



void serialize_object(struct byte_list *b_list, struct send_data *sd) {
    switch(sd->type) {

    }
}

void serialize_version(struct byte_list *b_list, struct send_data *sd) {
    struct byte_struct b_buf;
    b_buf = bytes_from_short(STREAM_VERSION);
    add_byte_to_list(b_buf, b_list);
}

void serialize_magic(struct byte_list *b_list, struct send_data *sd) {
    struct byte_struct b_buf;
    b_buf = bytes_from_short(STREAM_MAGIC);
    add_byte_to_list(b_buf, b_list);
}

struct byte_struct serialize(struct send_data sd) {
    struct byte_list b_list = init_byte_list();
    serialize_magic(&b_list, &sd);
    serialize_version(&b_list, &sd);
    serialize_object(&b_list, &sd);
    struct byte_struct bytes = list_to_bytes(b_list);
    return bytes;
}
