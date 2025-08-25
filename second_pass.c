#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "second_pass.h"
#include "globals.h"
#include "table.h"
#include "code_conversion.h"
#include "util.h"
#include "lexer.h"
#include "Errors.h"
#include "handle_text.h"

unsigned short word;
char *encoded;

int exe_second_pass(const char *filename) {
    FILE *fp, *ob_fp;
    char am_file[MAX_FILENAME_LENGTH];
    char ob_file[MAX_FILENAME_LENGTH];
    char line[MAX_LINE_LENGTH];
    int ic = IC_INIT_VALUE;
    int line_number = 0;

    sprintf(am_file, "%s.am", filename);
    sprintf(ob_file, "%s.ob", filename);


    fp = fopen(am_file, "r");
    if (!fp) {
        print_internal_error(ERR_FILE_OPEN);
        return 1;
    }

    ob_fp = fopen(ob_file, "w");
    if (!ob_fp) {
        print_internal_error(ERR_FILE_OPEN);
        fclose(fp);
        return 1;
    }

    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        char *curr = line;
        char *token;
        char src[MAX_LABEL_LENGTH] = "";
        char dest[MAX_LABEL_LENGTH] = "";
        line_number++;

        trim_whitespace(curr);
        if (curr[0] == ';' || curr[0] == '\0') continue;

        if (strchr(curr, ':')) {
            curr = skip_label(curr);
        }

        token = get_next_token(curr);
        if (!token) continue;

        if (is_opcode(token)) {
            sscanf(curr + strlen(token), "%s %s", src, dest);
            word = build_word(token, src, dest);
            encoded = short_to_special_base4(word);
            fprintf(ob_fp, "%04d %s\n", ic++, encoded);
            free(encoded);
        }
    }

    fclose(fp);
    fclose(ob_fp);
    return 0;
}

