#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "search.h"
#include "file_utils.h"

#define DEFAULT_DIR "~/files"

int main(int argc, char *argv[]) {
    char path[4096];

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <search_word> [directory]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *word = argv[1];

    if (argc >= 3) {
        expand_home_directory(argv[2], path);
    } else {
        expand_home_directory(DEFAULT_DIR, path);
    }

    search_in_directory(path, word);

    return EXIT_SUCCESS;
}