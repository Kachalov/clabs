#pragma once

#include <stdio.h>

int create_array(size_t num, size_t size, void **data);
void delete_array(void **data);
void offset_array(size_t k, size_t num, size_t size, void *data);
void print_int_array(size_t num, void *data);
void copy_int_array(size_t num, void *f, int *t_num, void **t);
