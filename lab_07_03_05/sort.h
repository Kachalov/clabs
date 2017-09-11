#pragma once

typedef int (*cmp_f_t)(const void *, const void *);

void sort(void *data, size_t num, size_t size, cmp_f_t cmp_f);

int cmp_int(const void *a, const void *b);
