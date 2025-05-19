#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include "search.h"

void to_lower_str(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

void search_file(const char *path, const char *word, int ignore_case) {
    FILE *file = fopen(path, "r");
    if (!file) {
        perror(path);
        return;
    }

    char line[4096];
    int line_number = 0;
    while (fgets(line, sizeof(line), file)) {
        line_number++;

        char *line_copy = NULL;
        char *word_copy = NULL;

        if (ignore_case) {
            line_copy = strdup(line);
            word_copy = strdup(word);
            if (!line_copy || !word_copy) {
                perror("strdup");
                fclose(file);
                return;
            }
            to_lower_str(line_copy);
            to_lower_str(word_copy);

            if (strstr(line_copy, word_copy)) {
                printf("%s:%d: %s", path, line_number, line);
            }

            free(line_copy);
            free(word_copy);
        } else {
            if (strstr(line, word)) {
                printf("%s:%d: %s", path, line_number, line);
            }
        }
    }

    fclose(file);
}

void search_directory(const char *dir_path, const char *word, int ignore_case) {
    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror(dir_path);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        struct stat path_stat;
        if (lstat(full_path, &path_stat) == -1) {
            perror(full_path);
            continue;
        }

        if (S_ISDIR(path_stat.st_mode)) {
            search_directory(full_path, word, ignore_case);
        } else if (S_ISREG(path_stat.st_mode)) {
            search_file(full_path, word, ignore_case);
        }
    }

    closedir(dir);
}
