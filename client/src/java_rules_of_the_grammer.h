#ifndef JAVA_RULES_OF_THE_GRAMMER_H
#define JAVA_RULES_OF_THE_GRAMMER

#include <stdio.h>

struct object {
    
};

struct blockdata {

};

struct magic {
    unsigned char *stread_magic;
};

struct version {
    unsigned char *stream_version;
};

struct contents {
    struct object o;
    struct blockdata b;
};

struct stream {
    struct magic m;
    struct version v;
    struct contents c;
};

unsigned char read_n_byte(size_t len);
struct magic analyze_magic();
struct version analyze_version();
struct contents analyze_contents();
struct stream analyze_stream();
void analyze_grammer(unsigned char *bytes, size_t len);

#endif
