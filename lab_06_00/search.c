#include <stdio.h>
#include <assert.h>
#include "search.h"
#include "io.h"

int find_max(int const *const arr, int *arr_size, int *max)
{
    assert(arr_size - arr <= ARRAY_SIZE);
    assert(arr_size - arr >= 0);
    assert(arr != NULL);
    assert(max != NULL);

    int max_new = 0;
    int *iter_l = (int *) arr;
    int *iter_r = (int *) arr_size - 1;

    if (iter_l == iter_r + 1)
        return ERR_NO_DATA;

    *max = *iter_l + *iter_r;
    while (++iter_l <= --iter_r)
    {
        max_new = *iter_l + *iter_r;
        if (max_new > *max)
            *max = max_new;
    }

    return OK;
}
