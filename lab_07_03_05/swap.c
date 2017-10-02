#include <stdlib.h>
#include <string.h>

#include "swap.h"
#include "errors.h"

int swap(void *a, void *b, size_t size)
{
    void *tmp = NULL;
    int err = OK;

    if ((tmp = malloc(size)) == NULL)
    {
        err = MEM_ALLOC_ERR;
    }
    else
    {
        memcpy(tmp, a, size);
        memcpy(a, b, size);
        memcpy(b, tmp, size);
        free(tmp);
    }

    return err;
}
