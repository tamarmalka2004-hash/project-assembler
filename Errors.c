#include <stdio.h>
#include "Errors.h"

const char *error_messages[] = {
    "No error",
    "Memory allocation failed",
    "Failed to open file",
    "Line too long",
    "Invalid syntax",
    "Unknown error"
};

void print_internal_error(ErrorCode code) {
    fprintf(stderr, "[Internal Error] %s\n", error_messages[code]);
}

void print_external_error(ErrorCode code, location loc) {
    fprintf(stderr, "[Error] %s in file %s at line %d\n",
            error_messages[code], loc.file_name, loc.line_num);
}
