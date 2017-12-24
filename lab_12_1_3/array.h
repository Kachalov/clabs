#pragma once

#include <stdio.h>

int process(FILE *fin, FILE *fout, int filtering);
void print_int_array(FILE *fd, const void *b,  const void *e);
int create_array_file(FILE *fd, size_t num, size_t size, void **data);
int create_array(size_t num, size_t size, void **data);
void delete_array(void **data);
int get_data_len(FILE *fd, size_t size, size_t *data_len);
