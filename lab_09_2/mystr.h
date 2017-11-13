#pragma once

#include <unistd.h>

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);
char *my_str_replace(const char *source, const char *search, const char *replace);
