#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include "search.h"
#include "file_utils.h"

void search_in_directory(const char *dirpath, const char *word) {
    DIR *dir = opendir(dirpath);
    if (!dir) {
        perror("openning dir err:");
        return;
    }

    struct dirent *entry;
    /*struct dirent {
        ino_t          d_ino;         inode number 
        off_t          d_off;         offset to the next dirent 
        unsigned short d_reclen;      length of this record 
        unsigned char  d_type;       type of file; not supported by all file system types 
        char           d_name[256];   filename 
    };
    */
    struct stat path_stat;
    char full_path[4096];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) //strcmp - если совпадают дает 0, s1 > s2 => >0, s1 < s2 => 0<; скипает служебные папки /. и /..
            continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", dirpath, entry->d_name); //форматирование строки 
        if (lstat(full_path, &path_stat) == -1) {
            perror(full_path);
            continue;
        }

        if (S_ISDIR(path_stat.st_mode)) { //S_ISDIR - dir
            search_in_directory(full_path, word);
        } else if (S_ISREG(path_stat.st_mode)) { // S_ISREG - file
            if (is_text_file(entry->d_name)) {
                search_in_file(full_path, word);
            }
        }
    }

    closedir(dir);
}
