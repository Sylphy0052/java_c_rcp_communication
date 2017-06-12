#include <stdio.h>

#include "parser.h"

int hexDump (char *desc, void *addr, int len, int progcount) {
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;
    // Output description if given.
    if (desc != NULL)
        printf ("%s:\n", desc);
    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return -1;
    }
    if (len < 0) {
        printf("  NEGATIVE LENGTH: %i\n",len);
        return -1;
    }
    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).
        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf ("  %s\n", buff);
            // Output the offset.
            printf ("  %04x ", i);
        }
        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);
        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }
    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }
    // And print the final ASCII bit.
    printf ("  %s\n", buff);
    return progcount + len;
}

void parse(unsigned char *byte_list, int length) {
    int pc = 0;
    hexDump("hexdump", byte_list, length, 0);
    pc = hexDump("magic", &byte_list[pc], 2, pc);
    pc = hexDump("version", &byte_list[pc], 2, pc);
}
