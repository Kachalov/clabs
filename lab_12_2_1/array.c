#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "array.h"
#include "errors.h"

int create_array(size_t num, size_t size, void **data)
{
    if (!*data)
    {
        *data = malloc(num * size);
        if (*data == NULL)
            return MEM_ALLOC_ERR;
    }

    return OK;
}

void delete_array(void **data)
{
    if (*data)
        free(*data);
    *data = NULL;
}

void offset_array(size_t k, size_t num, size_t size, void *data)
{
    void *tmp[size];

    for (size_t i = 0; i < k; i++)
    {
        memcpy(tmp, data, size);
        for (size_t j = 0; j < num - 1; j++)
            memcpy(((char *)data) + j * size, ((char *)data) + (j + 1) * size, size);
        memcpy((char *)data + (num - 1) * size, tmp, size);
    }
}

int is_pow(size_t num)
{
    for (size_t i = 0; i <= num; i++)
        if (i * i == num)
            return 1;
    return 0;
}

int copy_int_array(size_t num, void *f, int *t_num, void **t)
{
    size_t c = 0;
    int err = OK;

    for (int i = 0; i < num; i++)
        if (is_pow(((int *)f)[i]))
            (*t_num)++;

    err = create_array(*t_num, sizeof(int), t);

    if (!err)
        for (int i = 0; i < num; i++)
            if (is_pow(((int *)f)[i]))
                (*(int **)t)[c++] = ((int *)f)[i];

    return err;
}

void print_int_array(size_t num, void *data)
{
    for(int i = 0; i < num; i++)
        printf("%d ", ((int *)data)[i]);
    printf("\n");
}
