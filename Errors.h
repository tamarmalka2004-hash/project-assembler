#ifndef ERRORS_H
#define ERRORS_H

#include "globals.h"

typedef enum {
    ERR_OK = 0,
    ERR_MEM_ALLOC,
    ERR_FILE_OPEN,
    ERR_LINE_TOO_LONG,
    ERR_INVALID_SYNTAX,
    ERR_UNKNOWN
} ErrorCode;

void print_internal_error(ErrorCode code);
void print_external_error(ErrorCode code, location loc);

#endif
