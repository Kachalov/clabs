#include "search.h"

int find_max(int const *const arr, int arr_size, int *max)
{
    int max_new = 0;
    int *iter_l = (int *) arr;
    int *iter_r = (int *) arr + arr_size - 1;

    if (arr_size == 0)
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
