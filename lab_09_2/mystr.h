#pragma once

#include <unistd.h>

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);
char *my_str_replace(const char *source, const char *search, const char *replace);
int str_replace_size(const char *source, const char *search);
void str_replace_copy(char *cur, const char *src,
    const char *prev_src, const char *search, const char *replace);
