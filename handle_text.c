#include <ctype.h>
#include <string.h>
#include "handle_text.h"

void trim_whitespace(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}

char *skip_label(char *line) {
    char *colon = strchr(line, ':');
    return colon ? colon + 1 : line;
}

char *get_next_token(char *line) {
    char *start = line;
    while (*start && isspace((unsigned char)*start)) start++;
    if (!*start) return NULL;

    char *end = start;
    while (*end && !isspace((unsigned char)*end)) end++;

    if (*end) *end = '\0';
    return start;
}

