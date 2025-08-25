#ifndef TABLE_H
#define TABLE_H

#include "globals.h"

typedef enum {
    CODE,
    DATA,
    EXTERNAL,
    ENTRY
} SymbolType;

typedef struct Symbol {
    char name[MAX_LABEL_LENGTH];
    int address;
    SymbolType type;
    struct Symbol *next;
} Symbol;

void add_symbol(const char *name, int address, SymbolType type);
Symbol *find_symbol(const char *name);
void free_symbols();

#endif
