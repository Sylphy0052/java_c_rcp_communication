#include <stdio.h>

#include "hexdump.h"

size_t hexdump(char *desc, unsigned char *bytes, size_t len, size_t pc) {
    int i;
    size_t result_pc = pc;
    unsigned char buff[17];
    if(desc != NULL)
        printf("%s:\n", desc);
        if(len == 0) {
    printf("  ZERO LENGTH\n");
    return -1;
    }

    for (i = 0; i < len; i++) {
        if ((i % 16) == 0) {
            if (i != 0) {
                printf("  %s\n", buff);
            }
            printf("  %04x ", i);
        }
        printf(" %02x", bytes[i]);
        if((bytes[i] < 0x20) || (bytes[i] > 0x7e)) {
            buff[i % 16] = '.';
        } else {
            buff[i % 16] = bytes[i];
        }
        buff[(i % 16) + 1] = '\0';
    }
    while((i % 16) != 0) {
        printf("   ");
        i++;
    }
    printf ("  %s\n", buff);
    return (pc + len);
}
