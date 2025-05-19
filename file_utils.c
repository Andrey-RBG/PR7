#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "file_utils.h"

#define MAX_LINE_LENGTH 1024

void expand_home_directory(const char *path, char *expanded_path) {
    if (path[0] == '~') {
        const char *home = getenv("HOME");
        snprintf(expanded_path, 4096, "%s%s", home, path + 1);
    } else {
        strncpy(expanded_path, path, 4096);
    }
}

int is_text_file(const char *filename) {
    const char *ext = strrchr(filename, '.');
    return ext && strcmp(ext, ".txt") == 0;
}

void search_in_file(const char *filepath, const char *word) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror(filepath);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        if (strstr(line, word)) {
            printf("%s:%d: %s", filepath, line_number, line);
        }
    }

    fclose(file);
}
