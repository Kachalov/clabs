#include <stdio.h>
#include "io.h"

int read_array(FILE *fd, int *arr, int **arr_size)
{
    int tmp;
    int size = 0;

    while (fscanf(fd, "%d", &tmp) == 1)
    {
        if (size++ >= ARRAY_SIZE)
        {
            return ERR_DATA_OVERFLOW;
        }
        *((*arr_size)++) = tmp;
    }
    return OK;
}

void print_error(int err)
{
    switch(err)
    {
        case OK:
            break;

        case ERR_INVALID_DATA:
            fprintf(stderr, "Error (#%d): invalid data\n", err);
            break;

        case ERR_NO_DATA:
            fprintf(stderr, "Error (#%d): not enough data\n", err);
            break;

        case ERR_DATA_OVERFLOW:
            fprintf(stderr, "Error (#%d): too much data\n", err);
            break;

        case ERR_NO_FILE:
            fprintf(stderr, "Error (#%d): file not found\n", err);
            break;

        case ERR_NO_FILENAME:
            fprintf(stderr, "Error (#%d): no filename specified\n", err);
            break;

        default:
            fprintf(stderr, "Unknown error: #%d\n", err);
            break;
    }
}
