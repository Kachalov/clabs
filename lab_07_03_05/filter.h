#pragma once

#include "sort.h"

int filter(void *data, size_t num,
           size_t size,
           cmp_f_t cmp_f,
           void **data_new, size_t *num_new);
int filter_find_pos(int *begin, int *end);
