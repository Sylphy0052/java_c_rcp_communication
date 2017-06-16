#include "struct.h"

unsigned char *set_char() {
    printf("set_char\n");
    unsigned char *c = "string\0";
    printf("str : %s\n", c);
    return c;
}



void read_str2(struct str2 *s) {
    printf("read_str2\n");
    // struct str2 *s_ = malloc(sizeof(struct str2));
    // *s = s_;
    // s_->c = set_char();
    // printf("str2 : %s\n", s_->c);
    s->c = set_char();
    printf("str2 : %s\n", s->c);
}

void read_str1(struct str1 *s) {
    printf("read_str1\n");
    // struct str1 *s_ = malloc(sizeof(struct str1));
    // *s = s_;
    // read_str2(&s_->s2);
    // printf("str1 : %s\n", s_->s2.c);
    read_str2(&s->u.s2);
    printf("str1 : %s\n", s->u.s2.c);
}

void read_str(struct str **s) {
    // 二重ポインタの処理
    printf("read_str\n");
    struct str *s_ = malloc(sizeof(struct str));
    *s = s_;
    read_str1(&s_->s1);
    printf("str : %s\n", s_->s1.u.s2.c);
    // read_str1(&s->s1);
    // printf("str : %s\n", s->s1.s2.c);
}

int main(int argc, char const *argv[]) {
    // ずっと使う変数のmallocは二重ポインタで
    struct str *s = malloc(sizeof(struct str));
    read_str(&s);
    printf("main str : %s\n", s->s1.u.s2.c);
}
