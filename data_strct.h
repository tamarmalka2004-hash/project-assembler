#ifndef DATA_STRCT_H
#define DATA_STRCT_H

#include "globals.h"

typedef enum {
    INSTRUCTION,
    DIRECTIVE
} LineType;

typedef struct {
    LineType type;
    char label[MAX_LABEL_LENGTH];
    char opcode[10];
    char operands[2][MAX_LABEL_LENGTH];
    int operand_count;
    location loc;
} ParsedLine;

#endif

