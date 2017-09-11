#include <string.h>

#include "sort.h"
#include "swap.h"

void sort(void *data, size_t num, size_t size, cmp_f_t cmp_f)
{
    // TODO: Implement 7th algorithm

    if (num == 0)
        return;

    for (int i = 0; i < num - 1; i++)
        for (int j = i + 1; j < num; j++)
            if (cmp_f((char *)data + i * size, (char *)data + j * size) > 0)
                swap((void *)((char *)data + i * size), (void *)((char *)data + j * size), size);
}

int cmp_int(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
