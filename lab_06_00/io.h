#pragma once

#include "errors.h"

#define ARRAY_SIZE 100

int read_array(FILE *fd, int *arr, int *arr_size);
void print_error(int err);
