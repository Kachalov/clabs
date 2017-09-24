#include <string.h>

#include "sort.h"
#include "swap.h"

void sort(void *data, size_t num, size_t size, cmp_f_t cmp_f)
{
    int i = 0;
    int j = num - 1;

    if (num == 0)
        return;

    for (; i < j;)
    {
        for (int k = i; k < j; k++)
            if (cmp_f((char *)data + k * size, (char *)data + (k + 1) * size) > 0)
                swap(
                        (void *)((char *)data + k * size),
                        (void *)((char *)data + (k + 1) * size),
                        size
                );
        j--;

        for (int k = j; k > i; k--)
            if (cmp_f((char *)data + (k - 1) * size, (char *)data + k * size) > 0)
                swap(
                        (void *)((char *)data + k * size),
                        (void *)((char *)data + (k - 1) * size),
                        size
                );
        i++;
    }
}

int cmp_int(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
