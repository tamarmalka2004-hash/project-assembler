#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "globals.h"

const char *registers[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};
const char *opcodes[] = {
    "mov", "cmp", "add", "sub",
    "not", "clr", "lea", "inc",
    "dec", "jmp", "bne", "red",
    "prn", "jsr", "rts", "stop"
};

int is_register(const char *str) {
    int i;
    for (i = 0; i < 8; i++) {
        if (strcmp(str, registers[i]) == 0) return 1;
    }
    return 0;
}

int is_opcode(const char *str) {
    int i;
    for (i = 0; i < 16; i++) {
        if (strcmp(str, opcodes[i]) == 0) return 1;
    }
    return 0;
}

int is_number(const char *str) {
    int i = 0;
    if (str[0] == '-' || str[0] == '+') i++;
    for (; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int is_valid_label(const char *str) {
    int i, len = strlen(str);
    if (!isalpha(str[0]) || len > MAX_LABEL_LENGTH) return 0;
    for (i = 1; i < len; i++) {
        if (!isalnum(str[i])) return 0;
    }
    return !is_opcode(str) && !is_register(str);
}

