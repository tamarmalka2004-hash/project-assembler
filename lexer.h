#ifndef LEXER_H
#define LEXER_H

int is_register(const char *str);
int is_number(const char *str);
int is_valid_label(const char *str);
int is_opcode(const char *str);

extern const char *opcodes[16];

#endif

