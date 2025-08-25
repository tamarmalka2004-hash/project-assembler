#include <stdio.h>
#include <string.h>
#include "first_pass.h"
#include "handle_text.h"
#include "table.h"
#include "lexer.h"
#include "globals.h"
#include "Errors.h"

int exe_first_pass(const char *filename) {
    FILE *fp;
    char am_file[MAX_FILENAME_LENGTH];
    char line[MAX_LINE_LENGTH];
    int ic = IC_INIT_VALUE;
    int line_number = 0;

    snprintf(am_file, MAX_FILENAME_LENGTH, "%s.am", filename);
    fp = fopen(am_file, "r");
    if (!fp) {
        print_internal_error(ERR_FILE_OPEN);
        return 1;
    }

    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        char *curr = line;
        char label[MAX_LABEL_LENGTH] = "";
        char *token;
        line_number++;

        trim_whitespace(curr);
        if (curr[0] == ';' || curr[0] == '\0') continue;

        if (strchr(curr, ':')) {
            sscanf(curr, "%31[^:]", label);
            if (!is_valid_label(label)) {
                location loc = { (char *)filename, line_number };
                print_external_error(ERR_INVALID_SYNTAX, loc);
                continue;
            }
            add_symbol(label, ic, CODE);
            curr = skip_label(curr);
        }

        token = get_next_token(curr);
        if (!token) continue;

        if (strcmp(token, ".entry") == 0 || strcmp(token, ".extern") == 0) {
            continue;
        }
        if (is_opcode(token)) {
            ic += 1;
        }
    }

    fclose(fp);
    return 0;
}

