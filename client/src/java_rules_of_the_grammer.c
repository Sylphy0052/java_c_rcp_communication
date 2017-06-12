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

// unsigned char read_n_byte(size_t len) {
//     unsigned char *result = malloc(sizeof(unsigned char) * len);
//     int i;
//     for(i = pc; i < len; i++) {
//         result[i - pc] = b[i];
//     }
//     printf("result[0] : %02x, b[pc] : %02x\n", result[0], b[pc]);
//     pc += len;
//     return result;
// }

void analyze_classname() {
    // utf
}

void analyze_serialversionuid() {
    // long
}

void analyze_newhandle() {
    // The next number in sequence is assigned
    // to the object being serialized or deserialized
}

void analyze_classdescinfo() {
    // classDescFlags fields classAnnotation superClassDesc 
}

void analyze_newclassdesc() {
    switch(b[pc++]) {
    case TC_CLASSDESC:
        analyze_classname();
        analyze_serialversionuid();
        analyze_newhandle();
        analyze_classdescinfo();
    case TC_PROXYCLASSDESC:
        printf("undefined\n");
    }
}

void analyze_classdesc() {
    printf("analyze_classdesc\n");
    switch(b[pc]) {
    // newClassDesc | nullReference | (ClassDesc)prevObject
    case TC_CLASSDESC:
        analyze_newclassdesc();
        break;
    default:
        printf("undefined\n");
    }
}

void analyze_newhandle() {
    printf("analyze_newhandle\n");
}

void analyze_value() {
    printf("analyze_value\n");
}

void analyze_newobject() {
    printf("analyze_newobject\n");
    analyze_classdesc();
    analyze_newhandle();
    analyze_value();
}

void analyze_blockdata() {
    printf("analyze_blockdata\n");
}

void analyze_object() {
    printf("analyze_object\n");
    switch(b[pc++]) {
    case TC_OBJECT:
        analyze_newobject();
        break;
    default:
        printf("undefined\n");
    }
}

void analyze_magic() {
    // struct magic m;
    // m.stread_magic = malloc(sizeof(unsigned char) * 2);
    // m.stread_magic[0] = b[pc++];
    // m.stread_magic[1] = b[pc++];
    // m.stread_magic = read_n_byte(2);
    pc += 2;
    hexdump("magic", 2);
    // return m;
}

void analyze_version() {
    // struct version v;
    // v.stream_version = read_n_byte(2);
    pc += 2;
    hexdump("version", 2);
    // return v;
}

void analyze_contents() {
    // struct contents c;
    // unsigned char *next_data = read_n_byte(1);
    // printf("pc : %d, next : %02x\n", pc, next_data);
    switch(b[pc]) {
    case TC_BLOCKDATA:
    case TC_BLOCKDATALONG:
        analyze_blockdata();
        break;
    default:
        analyze_object();
        break;
    }
    // return c;
}

void analyze_stream() {
    analyze_magic();
    analyze_version();
    analyze_contents();
    // return s;
}

void analyze_grammer(unsigned char *bytes, size_t len) {
    b = malloc(sizeof(unsigned char) * len);
    b = bytes;
    pc = 0;
    hexdump("hexdump", len);
    // struct stream s;
    analyze_stream();
}
