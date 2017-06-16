#ifndef HEXDUMP_H
#define HEXDUMP_H

#include <stdio.h>

size_t hexdump(char *desc, unsigned char *bytes, size_t len, size_t pc);

#endif
