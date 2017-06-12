#ifndef JAVA_RULES_OF_THE_GRAMMER_H
#define JAVA_RULES_OF_THE_GRAMMER

#include <stdio.h>

#define STREAM_MAGIC 0xaced
#define STREAM_VERSION 5

#define TC_NULL 0x70
#define TC_REFERENCE 0x71
#define TC_CLASSDESC 0x72
#define TC_OBJECT 0x73
#define TC_STRING 0x74
#define TC_ARRAY 0x75
#define TC_CLASS 0x76
#define TC_BLOCKDATA 0x77
#define TC_ENDBLOCKDATA 0x78
#define TC_RESET 0x79
#define TC_BLOCKDATALONG 0x7A
#define TC_EXCEPTION 0x7B
#define TC_LONGSTRING  0x7C
#define TC_PROXYCLASSDESC 0x7D
#define TC_ENUM 0x7E

// struct object {
//
// };
//
// struct blockdata {
//
// };

// struct magic {
//     unsigned char *stread_magic;
// };
//
// struct version {
//     unsigned char *stream_version;
// };
//
// struct contents {
//     struct object o;
//     struct blockdata b;
// };
//
// struct stream {
//     struct magic m;
//     struct version v;
//     struct contents c;
// };

// unsigned char read_n_byte(size_t len);
// struct magic analyze_magic();
// struct version analyze_version();
// struct contents analyze_contents();
// struct stream analyze_stream();
void analyze_classname();
void analyze_serialversionuid();
void analyze_newhandle();
void analyze_classdescinfo();
void analyze_newclassdesc();
void analyze_classdesc();
void analyze_newhandle();
void analyze_value();
void analyze_newobject();
void analyze_blockdata();
void analyze_object();
void analyze_magic();
void analyze_version();
void analyze_contents();
void analyze_stream();
void analyze_grammer(unsigned char *bytes, size_t len);

#endif
