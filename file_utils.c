#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

int is_word_match(const char *token, const char *word) {
    return strcmp(token, word) == 0;
}

void search_in_file(const char *filepath, const char *word) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror(filepath);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int line_number = 0;

    while ((read = getline(&line, &len, file)) != -1) {
        line_number++;

        char *line_copy = strdup(line);

        char *token = strtok(line_copy, " \t\r\n.,");

        while (token) {
            if (is_word_match(token, word)) {
                printf("%s:%d: %s", filepath, line_number, line);
                break;
            }
            token = strtok(NULL, " \t\r\n.,");
        }

        free(line_copy);
    }

    free(line);
    fclose(file);
}
