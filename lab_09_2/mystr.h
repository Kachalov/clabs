#pragma once

#include <unistd.h>

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);
