#ifndef JAVA_RULES_OF_THE_GRAMMER_H
#define JAVA_RULES_OF_THE_GRAMMER_H

#include <stdio.h>

#define UTF_LENGTH 2
#define BYTE_LENGTH 8
#define UID_LENGTH 8

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

struct classname {
    char *name;
};

struct serialversionuid {
    unsigned long uid;
};

struct classdescflags {
    unsigned char *b;
};

struct primtypecode {
    unsigned char *code;
};

struct fieldname {
    unsigned char *name;
};

struct primitivedesc {
    struct primtypecode ptc;
    struct fieldname fn;
};

struct objectdesc {

};

struct fielddesc {
    union {
        struct primitivedesc pd;
        struct objectdesc od;
    } u;
    struct fielddesc *next;
};

struct fields {
    // <(short)<count>><fieldDesc[count]>
    unsigned short count;
    struct fielddesc fd;
};

struct classannotation {

};

struct superclassdesc {

};

struct classdescinfo {
    struct classdescflags cdf;
    struct fields f;
    struct classannotation ca;
    struct superclassdesc scd;
};

struct newhandle {
    unsigned short handle;
};

struct newclassdesc {
    struct classname cn;
    struct serialversionuid uid;
    struct newhandle nh;
    struct classdescinfo cdi;
};

struct nullreference {

};

struct prevobject {

};

struct classdesc {
    union {
        struct newclassdesc ncd;
        struct nullreference nr;
        struct prevobject po;
    } u;
};

struct classdata {

    struct classdata *next;
};

struct newobject {
    struct classdesc cd;
    struct newhandle nh;
    struct classdata cds;
};

struct newclass {

};

struct newarray {

};

struct newstring {

};

struct newenum {

};

struct exception {

};

struct object {
    union {
        struct newobject no;
        struct newclass nc;
        struct newarray na;
        struct newstring ns;
        struct newenum ne;
        struct newclassdesc ncd;
        struct prevobject po;
        struct nullreference nr;
        struct exception e;
    } u;
};

struct blockdata {

};

struct content {
    union {
        struct object o;
        struct blockdata b;
    } u;
    struct content *next;
};

struct magic {
    unsigned char *stread_magic;
};

struct version {
    unsigned char *stream_version;
};

struct contents {
    struct content c;
};

struct stream {
    struct magic m;
    struct version v;
    struct contents c;
};

void hexdump(const char *desc, const unsigned char *pc, const size_t len);
char *read_nibble(unsigned char *bytes);
char *read_n_byte(unsigned char *bytes, size_t len);
size_t analyze_classname(struct classname *cn, unsigned char *bytes);
size_t analyze_serialversionuid(struct serialversionuid *uid, unsigned char *bytes);
size_t analyze_classdescflags(struct classdescflags *cdf, unsigned char *bytes);
size_t analyze_primtypecode(struct primtypecode *ptc, unsigned char *bytes);
size_t analyze_fieldname(struct fieldname *fn, unsigned char *bytes);
size_t analyze_premitivedesc(struct primitivedesc *pd, unsigned char *bytes);
size_t analyze_fielddesc(struct fielddesc *fd, unsigned char *bytes, struct fielddesc *prev);
size_t analyze_fields(struct fields *f, unsigned char *bytes);
size_t analyze_classannotation(struct classannotation *ca, unsigned char *bytes);
size_t analyze_superclassdesc(struct superclassdesc *scd, unsigned char *bytes);
size_t analyze_classdescinfo(struct classdescinfo *cdi, unsigned char *bytes);
size_t analyze_newclassdesc(struct newclassdesc *ncd, unsigned char *bytes);
size_t analyze_classdesc(struct classdesc *cd, unsigned char *bytes);
size_t analyze_newhandle(struct newhandle *nh, unsigned char *bytes);
size_t analyze_newobject(struct newobject *no, unsigned char *bytes);
size_t analyze_object(struct object *o, unsigned char *bytes);
size_t analyze_content(struct content *c, unsigned char *byte);
size_t analyze_magic(struct magic *m, unsigned char *bytes);
size_t analyze_version(struct version *v, unsigned char *bytes);
size_t analyze_contents(struct contents *c, unsigned char *bytes, size_t len);
void analyze_stream(struct stream *s, unsigned char *bytes, size_t len);
void analyze_grammer(unsigned char *bytes, size_t len);

#endif
