#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "search.h"

int main(int argc, char *argv[]) {
    int ignore_case = 0;
    const char *word = NULL;
    const char *directory = NULL;

    // Аргумент парсинга
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            ignore_case = 1;
        } else if (!word) {
            word = argv[i];
        } else if (!directory) {
            directory = argv[i];
        }
    }

    if (!word) {
        fprintf(stderr, "Usage: %s [-i] <word> [directory]\n", argv[0]);
        return 1;
    }

    char default_dir[PATH_MAX];
    if (!directory) {
        const char *home = getenv("HOME");
        if (!home) {
            fprintf(stderr, "HOME not set.\n");
            return 1;
        }
        snprintf(default_dir, PATH_MAX, "%s/files", home);
        directory = default_dir;
    }

    search_directory(directory, word, ignore_case);
    return 0;
}
