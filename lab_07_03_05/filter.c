#include <string.h>

#include "filter.h"
#include "array.h"
#include "errors.h"

int filter(void *b, void *e, void **new_b, void **new_e)
{
    int err = OK;
    int p = filter_find_pos((int *)b, (int *)e);

    if ((err = create_array(p, sizeof(int), new_b)) != OK)
        return err;

    *new_e = (char *)*new_b + p * sizeof(int);
    memcpy(*new_b, b, p * sizeof(int));

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
