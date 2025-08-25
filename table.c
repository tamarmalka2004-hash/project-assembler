#include <string.h>
#include <stdlib.h>
#include "table.h"
#include "util.h"

static Symbol *symbol_table = NULL;

void add_symbol(const char *name, int address, SymbolType type) {
    Symbol *new_symbol = handle_malloc(sizeof(Symbol));
    strncpy(new_symbol->name, name, MAX_LABEL_LENGTH);
    new_symbol->address = address;
    new_symbol->type = type;
    new_symbol->next = symbol_table;
    symbol_table = new_symbol;
}

Symbol *find_symbol(const char *name) {
    Symbol *curr = symbol_table;
    while (curr) {
        if (strcmp(curr->name, name) == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

void free_symbols() {
    Symbol *curr = symbol_table;
    while (curr) {
        Symbol *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    symbol_table = NULL;
}

