#include <stdlib.h>
#include <string.h>

#include "person.h"
#include "mystruct.h"
#include "java_rules_of_the_grammer.h"
#include "serialize.h"

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
    s >>= BYTE_LENGTH;
  }
  return bytes;
}

struct byte_struct bytes_from_int(unsigned int integer) {
  struct byte_struct bytes;
  bytes.len = 4;
  bytes.contents = malloc(sizeof(char) * bytes.len);
  for (size_t i = 1; i <= bytes.len; i++) {
    bytes.contents[bytes.len - i] = (unsigned char)integer;
    integer >>= BYTE_LENGTH;
  }
  return bytes;
}

struct byte_struct bytes_from_long(unsigned long l) {
  struct byte_struct bytes;
  bytes.len = 8;
  bytes.contents = malloc(sizeof(char) * bytes.len);
  for (size_t i = 1; i <= bytes.len; i++) {
    bytes.contents[bytes.len - i] = (unsigned char)l;
    l >>= BYTE_LENGTH;
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
    slen >>= BYTE_LENGTH;
  }
  return bytes;
}

void serialize_fieldname(struct byteb_list *b_list, struct send_field *f) {
    printf("fieldname\n");
    add_byte_to_list(bytes_from_string(f->sd->name), b_list);
}

void serialize_object_field(struct byte_list *b_list, struct send_field *f) {
    printf("object_field\n");
    add_byte_to_list(bytes_from_char(f->d.sd->type), b_list);
    switch(f->d.sd->type) {
    case TC_OBJECT:
        serialize_newobject(b_list, f->sd);
        break;
  // case TC_REFERENCE:
  //   break;
    case TC_STRING:
        serialize_newstring(b_list, f->d.sd);
        printf("object_field : %s\n", f->d.sd->name);
        break;
    default:
        hexdump("Undefined -object-", &f->sd->type, 1);
  }
}

void serialize_classname1(struct byteb_list *b_list, struct send_field *f) {
    printf("classname1\n");
    serialize_object_field(b_list, f);
}

void serialize_fielddesc(struct byteb_list *b_list, struct send_field *f) {
    printf("fielddesc\n");
    add_byte_to_list(bytes_from_char(f->sd->type), b_list);
    switch(f->sd->type) {
        case 'L':
            serialize_fieldname(b_list, f);
            serialize_classname1(b_list, f);
            break;
    }
}

void serialize_classdescflags(struct byte_list *b_list, struct send_data *sd) {
    printf("classdescflags\n");
    add_byte_to_list(bytes_from_char(sd->flag), b_list);
}

void serialize_fields(struct byte_list *b_list, struct send_data *sd) {
    printf("fields\n");
    unsigned short len = 0;
    struct send_field *f = &sd->f;
    len++;
    add_byte_to_list(bytes_from_short(len), b_list);
    serialize_fielddesc(b_list, f);
}

void serialize_classannotation(struct byte_list *b_list, struct send_data *sd) {
    printf("classannotation\n");
    add_byte_to_list(bytes_from_char(TC_ENDBLOCKDATA), b_list);
}

void serialize_superclassdesc(struct byte_list *b_list, struct send_data *sd) {
    printf("superclassdesc\n");
    serialize_classdesc(b_list, NULL);
}

void serialize_classname(struct byte_list *b_list, struct send_data *sd) {
    printf("classname\n");
    add_byte_to_list(bytes_from_string(sd->name), b_list);
}

void serialize_serialversionuid(struct byte_list *b_list, struct send_data *sd) {
    printf("serialversionuid\n");
    add_byte_to_list(bytes_from_long(sd->uid), b_list);
}

void serialize_classdescinfo(struct byte_list *b_list, struct send_data *sd) {
    printf("classdescinfo\n");
    serialize_classdescflags(b_list, sd);
    serialize_fields(b_list, sd);
    serialize_classannotation(b_list, sd);
    serialize_superclassdesc(b_list, sd);
}

void serialize_nullreference(struct byte_list *b_list, struct send_data *sd) {
    printf("serialize_nullreference\n");
    add_byte_to_list(bytes_from_char(TC_NULL), b_list);
}

void serialize_newclassdesc(struct byte_list *b_list, struct send_data *sd) {
    printf("newclassdesc\n");
    add_byte_to_list(bytes_from_char(TC_CLASSDESC), b_list);
    printf("classname : %s\n", sd->name);
    serialize_classname(b_list, sd);
    serialize_serialversionuid(b_list, sd);
    serialize_classdescinfo(b_list, sd);
}

void serialize_classdesc(struct byte_list *b_list, struct send_data *sd) {
    printf("classdesc\n");
    if(sd == NULL) {
        printf("NULL\n");
        serialize_nullreference(b_list, sd);
    } else {
        serialize_newclassdesc(b_list, sd);
        printf("ret serialize_classdesc\n");
    }
}

void serialize_classdata(struct byte_list *b_list, struct send_data *sd) {
    struct send_field *f = &sd->f;
    struct data *d = &sd->d;

    switch (f->sd->type) {
    case 'L':
        serialize_object(b_list, d->sd);
        break;
    default:
        hexdump("Undefined -classdata-", &f->sd->type, 1);
    }
}

void serialize_newobject(struct byte_list *b_list, struct send_data *sd) {
    printf("newobject\n");
    serialize_classdesc(b_list, sd);
    serialize_classdata(b_list, sd);
}

void serialize_newstring(struct byte_list *b_list, struct send_data *sd) {
    printf("newstring\n");
    add_byte_to_list(bytes_from_string(sd->name), b_list);
}

void serialize_object(struct byte_list *b_list, struct send_data *sd) {
    printf("object\n");
    add_byte_to_list(bytes_from_char(sd->type), b_list);
    switch(sd->type) {
    case TC_OBJECT:
        serialize_newobject(b_list, sd);
        break;
  // case TC_REFERENCE:
  //   break;
    case TC_STRING:
        serialize_newstring(b_list, sd);
        break;
    default:
        hexdump("Undefined -object-", &sd->type, 1);
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
    printf("===Serialize===\n");
    struct byte_list b_list = init_byte_list();
    serialize_magic(&b_list, &sd);
    serialize_version(&b_list, &sd);
    serialize_object(&b_list, &sd);
    struct byte_struct bytes = list_to_bytes(b_list);
    hexdump("bytes", bytes.contents, bytes.len);
    return bytes;
}
