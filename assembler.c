#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preproc.h"
#include "first_pass.h"
#include "second_pass.h"
#include "util.h"

int main(int argc, char *argv[]) {
    int i;
    char *input_file;
    for (i = 1; i < argc; i++) {
        input_file = argv[i];

        if (!mcro_exec(input_file)) {
            printf("Macro processing failed for %s\n", input_file);
            continue;
        }

        if (exe_first_pass(input_file)) {
            printf("First pass failed for %s\n", input_file);
            continue;
        }

        if (exe_second_pass(input_file)) {
            printf("Second pass failed for %s\n", input_file);
            continue;
        }

        printf("Assembly successful for: %s\n", input_file);
    }
    return 0;
}

