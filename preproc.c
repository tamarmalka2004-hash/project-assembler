#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "util.h"
#include "Errors.h"
#include "handle_text.h"
#include "lexer.h"
#include "table.h"

#define MAX_MACRO_NAME 31
#define MAX_MACRO_CONTENT 500
#define MAX_MACROS 50

/* מבנה למאקרו */
typedef struct {
    char name[MAX_MACRO_NAME];
    char content[MAX_MACRO_CONTENT];
} Macro;

/* טבלת מאקרואים */
static Macro macro_table[MAX_MACROS];
static int macro_count = 0;

void add_macro(const char *name, const char *content) {
    if (macro_count < MAX_MACROS) {
        strncpy(macro_table[macro_count].name, name, MAX_MACRO_NAME);
        strncpy(macro_table[macro_count].content, content, MAX_MACRO_CONTENT);
        macro_count++;
    }
}

char *get_macro_content(const char *name) {
    int i;
    for (i = 0; i < macro_count; i++) {
        if (strcmp(macro_table[i].name, name) == 0) {
            return macro_table[i].content;
        }
    }
    return NULL;
}

int mcro_exec(const char *filename) {
    FILE *as_file = NULL, *am_file = NULL;
    char line[MAX_LINE_LENGTH];
    char as_file_name[MAX_FILENAME_LENGTH];
    char am_file_name[MAX_FILENAME_LENGTH];
    char macro_name[MAX_LINE_LENGTH] = {0};
    char macro_content[MAX_MACRO_CONTENT] = {0};
    int in_macro = 0;

    sprintf(as_file_name, "%s.as", filename);
    sprintf(am_file_name, "%s.am", filename);

    printf(">> [DEBUG] Opening source file: %s\n", as_file_name);

    as_file = fopen(as_file_name, "r");
    if (!as_file) {
        fprintf(stderr, "Error: Cannot open source file %s\n", as_file_name);
        return 0;
    }

    am_file = fopen(am_file_name, "w");
    if (!am_file) {
        fprintf(stderr, "Error: Cannot create .am file %s\n", am_file_name);
        fclose(as_file);
        return 0;
    }

    while (fgets(line, MAX_LINE_LENGTH, as_file)) {
        char original_line[MAX_LINE_LENGTH];
        char *token;

        strncpy(original_line, line, MAX_LINE_LENGTH);
        token = strtok(line, " \t\n");

        if (!token) {
            fprintf(am_file, "%s", original_line);
            continue;
        }

        if (strcmp(token, "macro") == 0) {
            token = strtok(NULL, " \t\n");
            if (!token) continue;
            strncpy(macro_name, token, MAX_LINE_LENGTH);
            macro_content[0] = '\0';
            in_macro = 1;
            continue;
        }

        if (in_macro) {
            if (strcmp(token, "endm") == 0) {
                add_macro(macro_name, macro_content);
                in_macro = 0;
            } else {
                strncat(macro_content, original_line, MAX_LINE_LENGTH);
            }
            continue;
        }

        {
            char *macro_expansion = get_macro_content(token);
            if (macro_expansion) {
                fprintf(am_file, "%s", macro_expansion);
            } else {
                fprintf(am_file, "%s", original_line);
            }
        }
    }

    fclose(as_file);
    fclose(am_file);
    return 1;
}

