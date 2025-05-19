#ifndef FILE_UTILS_H
#define FILE_UTILS_H

void expand_home_directory(const char *path, char *expanded_path);
int is_text_file(const char *filename);
void search_in_file(const char *filepath, const char *word);

#endif
