#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "errors.h"

void print_int_array(FILE *fd, const void *b, const void *e)
{
    for(int *it = (int *)b; it < (int *)e; it++)
    {
        printf("%d ", *it);
        fprintf(fd, "%d ", *it);
    }
    printf("\n");
    fprintf(fd, "\n");
}

int create_array_file(FILE *fd, size_t num, size_t size, void **data)
{
    int err = OK;
    void *it = NULL;
    int tmp = 0;

    fseek(fd, 0, SEEK_SET);
    if ((err = create_array(num, size, data)) != OK)
        return err;
    it = *data;

    while (fscanf(fd, "%d", &tmp) == 1)
    {
        memcpy(it, &tmp, size);
        it = (char *)it + size;
    }

    fseek(fd, 0, SEEK_SET);
    return OK;
}

int create_array(size_t num, size_t size, void **data)
{
    *data = malloc(num * size);
    if (*data == NULL)
        return MEM_ALLOC_ERR;

    return OK;
}

void delete_array(void **data)
{
    free(*data);
    *data = NULL;
}
