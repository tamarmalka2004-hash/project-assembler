#ifndef GLOBALS_H
#define GLOBALS_H

#define MAX_LINE_LENGTH 82
#define MAX_LABEL_LENGTH 31
#define IC_INIT_VALUE 100
#define MAX_MEMORY 256
#define MAX_FILENAME_LENGTH 100

#define TRUE 1
#define FALSE 0

typedef struct {
    char *file_name;
    int line_num;
} location;

#endif

