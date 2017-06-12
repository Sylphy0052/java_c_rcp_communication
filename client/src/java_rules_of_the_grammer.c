#include <stdio.h>

#include "java_rules_of_the_grammer.h"

unsigned char* b;
size_t pc;

void hexdump(char *desc, size_t len) {
    int i;
    unsigned char buff[17];
    int flag = 0;
    size_t pointer;
    if (pc < len) {
        pointer = 0;
        flag = 1;
    } else {
        pointer = pc - len;
    }
    if(desc != NULL)
        printf("%s:\n", desc);
        if(len == 0) {
    printf("  ZERO LENGTH\n");
    }

    printf("pc : %d\n", pointer);
    for (i = pointer; i < pointer + len; i++) {
        if(flag == 1) {
            if ((i % 16) == 0) {
                if (i != 0) {
                    printf("  %s\n", buff);
                }
                printf("  %04x ", i);
            }
        }
        printf(" %02x", b[i]);
        if((b[i] < 0x20) || (b[i] > 0x7e)) {
            buff[i % 16] = '.';
        } else {
            buff[i % 16] = b[i];
        }
        buff[(i % 16) + 1] = '\0';
    }
    while((i % 16) != 0) {
        printf("   ");
        i++;
    }
    while((i % 16) != 0) {
        printf("   ");
        i++;
    }
    printf ("  %s\n", buff);
}

unsigned char read_n_byte(size_t len) {
    unsigned char *result = malloc(sizeof(unsigned char) * len);
    int i;
    for(i = pc; i < len; i++) {
        result[i - pc] = b[i];
    }
    pc += len;
    return result;
}

struct magic analyze_magic() {
    struct magic m;
    m.stread_magic = read_n_byte(2);
    hexdump("magic", 2);
    return m;
}

struct version analyze_version() {
    struct version v;
    v.stream_version = read_n_byte(2);
    hexdump("version", 2);
    return v;
}

struct contents analyze_contents() {
    struct contents c;
    return c;
}

struct stream analyze_stream() {
    struct stream s;
    s.m = analyze_magic();
    s.v = analyze_version();
    s.c = analyze_contents();
    return s;
}

void analyze_grammer(unsigned char *bytes, size_t len) {
    b = malloc(sizeof(unsigned char) * len);
    b = bytes;
    pc = 0;
    hexdump("hexdump", len);
    pc = 0;
    struct stream s;
    s = analyze_stream();
}
