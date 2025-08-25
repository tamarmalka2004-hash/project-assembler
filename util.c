#include <stdio.h>
#include <stdlib.h>
#include "util.h"


/* Wrapper for malloc with error handling */
void *handle_malloc(unsigned int size) {
void *ptr = malloc(size);
if (!ptr) {
fprintf(stderr, "Memory allocation failed\n");
exit(1);
}
return ptr;
}


/* Converts a 10-bit number to binary string, e.g., "0101010101" */
char *short_to_binary(unsigned short num) {
int i;
char *res = handle_malloc(11); /* 10 bits + null terminator */
for (i = 9; i >= 0; i--) {
res[9 - i] = (num & (1 << i)) ? '1' : '0';
}
res[10] = '\0';
return res;
}
