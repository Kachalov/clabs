#include <stdio.h>

#define ARRAY_SIZE 100

#define OK 0
#define ERR_INVALID_DATA 1
#define ERR_NO_DATA 2
#define ERR_DATA_OVERFLOW 3
#define ERR_NO_FILE 4
#define ERR_NO_FILENAME 5


int read_array(FILE *fd, int *arr, int *arr_size);
int find_max(int const *const arr, int arr_size, int *max);
void print_error(int err);

int main(int argc, char **argv)
{
    int arr[ARRAY_SIZE] = {0};
    int arr_size = 0;
    int max = 0;
    int err = OK;
    char *fn = NULL;
    FILE *fd = NULL;

    if (argc <= 1)
    {
        err = ERR_NO_FILENAME;
        goto fail;
    }

    fn = argv[1];
    if ((fd = fopen(fn, "r")) == NULL)
    {
        err = ERR_NO_FILE;
        goto fail;
    }

    err = read_array(fd, arr, &arr_size);
    if (err == ERR_DATA_OVERFLOW)
        print_error(err);
    else if (err != OK)
        goto fail;
    
    if ((err = find_max(arr, arr_size, &max)) != OK)
        goto fail;

    printf("Max: %d\n", max);

    fail:
    if (err != OK)
        print_error(err);
    if (fd != NULL)
        fclose(fd);
    return err == OK ? 0 : 1;
}

int read_array(FILE *fd, int *arr, int *arr_size)
{
    int *iter = arr;
    int tmp;
    *arr_size = 0;

    while (fscanf(fd, "%d", &tmp) == 1)
    {
        if (*arr_size >= ARRAY_SIZE)
        {
            return ERR_DATA_OVERFLOW;
        }
        *(iter++) = tmp;
        ++(*arr_size);
    }
    return OK;
}

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

