#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preproc.h"
#include "util.h"

#define MAX_MACRO_NAME 31
#define MAX_MACRO_BODY 1000

typedef struct Macro {
    char name[MAX_MACRO_NAME];
    char body[MAX_MACRO_BODY];
    struct Macro *next;
} Macro;

static Macro *macros = NULL;

static void add_macro(const char *name, const char *body) {
    Macro *new_macro = handle_malloc(sizeof(Macro));
    strncpy(new_macro->name, name, MAX_MACRO_NAME);
    strncpy(new_macro->body, body, MAX_MACRO_BODY);
    new_macro->next = macros;
    macros = new_macro;
}

static Macro *find_macro(const char *name) {
    Macro *curr = macros;
    while (curr) {
        if (strcmp(curr->name, name) == 0) return curr;
        curr = curr->next;
    }
    return NULL;
}

int mcro_exec(const char *filename) {
    char line[MAX_LINE_LENGTH];
    char macro_name[MAX_MACRO_NAME];
    char macro_body[MAX_MACRO_BODY] = "";
    int inside_macro = 0;
    FILE *fp = NULL, *out_fp = NULL;
    char am_file[MAX_FILENAME_LENGTH];

    sprintf(am_file, "%s.am", filename);

    fp = fopen(filename, "r");
    if (!fp) return 0;

    out_fp = fopen(am_file, "w");
    if (!out_fp) return 0;

    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        if (strncmp(line, "macro", 5) == 0) {
            sscanf(line, "macro %s", macro_name);
            macro_body[0] = '\0';
            inside_macro = 1;
            continue;
        }
        if (strncmp(line, "endm", 4) == 0 && inside_macro) {
            add_macro(macro_name, macro_body);
            inside_macro = 0;
            continue;
        }
        if (inside_macro) {
            strncat(macro_body, line, MAX_MACRO_BODY - strlen(macro_body) - 1);
        } else {
            Macro *m = find_macro(line);
            if (m) {
                fputs(m->body, out_fp);
            } else {
                fputs(line, out_fp);
            }
        }
    }
    fclose(fp);
    fclose(out_fp);
    return 1;
}

