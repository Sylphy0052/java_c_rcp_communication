#include <stdio.h>

#include "parser.h"
#include "mystruct.h"
#include "java_rules_of_the_grammer.h"

void parse(struct byte_struct bytes_str) {
    unsigned char *bytes = bytes_str.contents;
    size_t length = bytes_str.len;
    analyze_grammer(bytes, length);

    // hexdump("hexdump", &bytes, length, 0);
    // pc = hexdump("magic", &bytes[pc], 2, pc);
    // pc = hexdump("version", &bytes[pc], 2, pc);
}
