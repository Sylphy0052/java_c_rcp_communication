#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "person.h"
#include "mystruct.h"

struct byte_struct bytes_from_char(unsigned char c);
struct byte_struct bytes_from_short(unsigned short s);
struct byte_struct bytes_from_int(unsigned int integer);
struct byte_struct bytes_from_long(unsigned long l);
struct byte_struct bytes_from_string(char *str);

void serialize_classdesc(struct byte_list *b_list, struct send_data *sd);
void serialize_newobject(struct byte_list *b_list, struct send_data *sd);
void serialize_newstring(struct byte_list *b_list, struct send_data *sd);
void serialize_object(struct byte_list *b_list, struct send_data *sd);
struct byte_struct serialize(struct send_data sd);

#endif
