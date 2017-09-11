#include <stdlib.h>
#include <string.h>

#include "swap.h"
#include "errors.h"

int swap(void *a, void *b, size_t size)
{
    void *tmp = NULL;
    int err = OK;

    if ((tmp = malloc(size)) == NULL)
        goto exit;

    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);

    exit:
    if (tmp != NULL)
        free(tmp);
    return err;
}
