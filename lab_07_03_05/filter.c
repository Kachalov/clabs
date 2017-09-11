#include <string.h>

#include "filter.h"
#include "array.h"
#include "errors.h"

int filter(void *data, size_t num,
           size_t size,
           cmp_f_t cmp_f,
           void **data_new, size_t *num_new)
{
    int err = OK;
    int p = filter_find_pos((int *)data, (int *)data + num);

    if ((err = create_array(p, size, data_new)) != OK)
        return err;

    memcpy(*data_new, data, p * size);
    *num_new = p;

    return OK;
}

int filter_find_pos(int *begin, int *end)
{
    int pos = end - begin;
    int i = pos;

    for (int *it = end - 1; it >= begin; it--, i--)
    {
        if (*it < 0)
        {
            pos = i;
            break;
        }
    }

    return pos;
}
