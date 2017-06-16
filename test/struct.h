struct str2 {
    unsigned char *c;
};

struct str1 {
    union {
        struct str2 s2;
    } u;
};

struct str {
    struct str1 s1;
};
