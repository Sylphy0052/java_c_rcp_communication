#ifndef JAVA_RULES_OF_THE_GRAMMER_H
#define JAVA_RULES_OF_THE_GRAMMER_H

#include <stdio.h>

#include "handle.h"

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
#define BASE_WIRE_HANDLE 0x7E0000

#define PRIMITIVE 0x00
#define OBJECT 0x01

struct classname {
    unsigned char *name;
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

struct objtypecode {
    unsigned char *code;
};

struct classname1 {
    // <(String)object>
    struct object *o;
};

struct objectdesc {
    // <objectDesc> ::= <obj_typecode><fieldName><className1>
    struct objtypecode otc;
    struct fieldname fn;
    struct classname1 cn1;
};

struct fielddesc {
    unsigned char type;
    union {
        struct primitivedesc pd;
        struct objectdesc od;
    } u;
    struct fielddesc *next;
};

struct fields {
    // <(short)<count>><fieldDesc[count]>
    unsigned short count;
    struct fielddesc *fd;
};

struct classannotation {
    struct contents *c;
};

struct superclassdesc {
    struct classdesc *cd;
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

struct prevobject {
    struct handle *h;
};

struct classdesc {
    union {
        struct newclassdesc ncd;
        struct prevobject po;
    } u;
};

struct nowrclass {
    unsigned char *values;
};

struct wrclass {
    struct nowrclass uc;
};

struct externalcontent {
    // (bytes) | object
    unsigned char *next;
};

struct externalcontents {
    struct externalcontent ec;
};

struct objectannotation {
    // endBlockData | contents endBlockData
    struct contents *c;
};

struct wrclass_t {
    struct wrclass wc;
    struct objectannotation oa;
};

struct classdata {
    // <nowrclass> | <wrclass><objectAnnotation> | <externalContents> | <objectAnnotation>
    // union {
    //     struct nowrclass nc;
    //     struct wrclass_t wct;
    //     struct externalcontents ec;
    //     struct objectannotation oa;
    // } u;
    union {
        // int
        int i;
        // byte
        char b;
        // Object
        struct object *o;
    } u;
    struct classdata *next;
};

struct newobject {
    struct classdesc cd;
    struct newhandle nh;
    struct classdata *cds;
};

struct newclass {

};

struct newarray {
    // <TC_ARRAY><classDesc><newHandle><(int)<size>><values[size]>
    // struct classdesc cd;
    // struct newhandle nh;
    // int s;
    // struct values v;
};

struct newstring {
    // <newString> ::= <TC_STRING><newHandle><(utf)> | <TC_LONGSTRING><newHandle><(long-utf)>
    struct newhandle nh;
    unsigned char *utf;
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
// char *read_nibble(const unsigned char *bytes);
unsigned char *read_n_byte(const unsigned char *bytes, size_t len);
size_t analyze_classname(struct classname *cn, const unsigned char *bytes);
size_t analyze_serialversionuid(struct serialversionuid *uid, const unsigned char *bytes);
size_t analyze_classdescflags(struct classdescflags *cdf, const unsigned char *bytes);
size_t analyze_primtypecode(struct primtypecode *ptc, const unsigned char *bytes);
size_t analyze_fieldname(struct fieldname *fn, const unsigned char *bytes);
size_t analyze_premitivedesc(struct primitivedesc *pd, const unsigned char *bytes);
size_t analyze_objtypecode(struct objtypecode *otc, const unsigned char *bytes);
size_t analyze_classname1(struct classname1 *cn1, const unsigned char *bytes);
size_t analyze_objectdesc(struct objectdesc *od, const unsigned char *bytes);
size_t analyze_fielddesc(struct fielddesc *fd, const unsigned char *bytes);
size_t analyze_fields(struct fields *f, const unsigned char *bytes);
size_t analyze_classannotation(struct classannotation *ca, const unsigned char *bytes);
size_t analyze_superclassdesc(struct superclassdesc *scd, const unsigned char *bytes);
void analyze_newhandle_ncd(struct newclassdesc *ncd);
size_t analyze_classdescinfo(struct classdescinfo *cdi, const unsigned char *bytes);
size_t analyze_newclassdesc(struct newclassdesc *ncd, const unsigned char *bytes);
size_t analyze_classdesc(struct classdesc *cd, const unsigned char *bytes);
void analyze_newhandle_no(struct newobject *no);
size_t analyze_classdata(struct classdata *cd, const unsigned char *bytes, struct fielddesc *fd);
size_t analyze_newobject(struct newobject *no, const unsigned char *bytes);
void analyze_newhandle_ns(struct newstring *ns);
size_t analyze_newstring(struct newstring *ns, const unsigned char *bytes);
size_t analyze_prevobject(struct prevobject *po, const unsigned char *bytes);
size_t analyze_object(struct object *o, const unsigned char *bytes);
size_t analyze_content(struct content *c, const unsigned char *byte);
size_t analyze_magic(struct magic *m, const unsigned char *bytes);
size_t analyze_version(struct version *v, const unsigned char *bytes);
size_t analyze_contents(struct contents *c, const unsigned char *bytes, size_t len);
void analyze_stream(struct stream **s, const unsigned char *bytes, size_t len);
struct stream analyze_grammer(const unsigned char *bytes, size_t len);

#endif
