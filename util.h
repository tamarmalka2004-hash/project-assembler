#ifndef UTIL_H
#define UTIL_H

#include "globals.h"

void *handle_malloc(unsigned int size);
char *short_to_binary(unsigned short num);
char *short_to_special_base4(unsigned short value);
#endif

