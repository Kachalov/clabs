#include <stdio.h>
#include <assert.h>

#define ARRAY_SIZE 100

#define OK 0
#define ERR_NO_FILENAME 1
#define ERR_NO_FILE 2
#define ERR_INVALID_DATA 3
#define ERR_NO_DATA 4

void print_error(int err);
int read_array(FILE *fd, int *arr, int *arr_size);
void sort_array(int *arr, int arr_size);
void print_array(int *const arr, int arr_size);
void move_element(int *arr, int from, int to);

int main(int argc, char **argv)
{
    int err = OK;
    int arr[ARRAY_SIZE] = {0};
    int arr_size = 0;
    FILE *fd = NULL;

    setbuf(stdout, NULL);

    if (argc < 2)
    {
        err = ERR_NO_FILENAME;
        goto fail;
    }

    fd = fopen(argv[1], "r");
    if (fd == NULL)
    {
        err = ERR_NO_FILE;
        goto fail;
    }

    if ((err = read_array(fd, arr, &arr_size)) != OK)
        goto fail;

    sort_array(arr, arr_size);
    print_array(arr, arr_size);

    fail:
    if (err != OK)
        print_error(err);
    if (fd != NULL)
        fclose(fd);
    return err != OK;
}

void print_error(int err)
{
    assert(err != OK);

    fprintf(stderr, "Error: ");
    switch (err)
    {
        case ERR_INVALID_DATA:
            fprintf(stderr, "invalid data");
            break;

        case ERR_NO_DATA:
            fprintf(stderr, "no data");
            break;

        case ERR_NO_FILE:
            fprintf(stderr, "file not found");
            break;

        case ERR_NO_FILENAME:
            fprintf(stderr, "no filename specified");
            break;

        default:
            fprintf(stderr, "#%d", err);
            break;
    }
    fprintf(stderr, "\n");
}

int read_array(FILE *fd, int *arr, int *arr_size)
{
    int err = OK;
    assert(fd != NULL);
    assert(arr_size != NULL);

    if (fscanf(fd, "%d", arr_size) != 1)
    {
        err = ERR_NO_DATA;
        goto fail;
    }

    for (int i = 0; i < *arr_size; i++)
    {
        if (fscanf(fd, "%d", &arr[i]) != 1)
        {
            err = ERR_INVALID_DATA;
            goto fail;
        }
    }

    fail:
    if (err != OK)
    {
        *arr_size = 0;
    }

    return err;
}

void sort_array(int *arr, int arr_size)
{
    int pos = 0;

    for (int i = 0; i < arr_size; i++)
    {
        if (arr[i] >= 0)
        {
            move_element(arr, i, pos++);
        }
    }
}

void print_array(int *const arr, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void move_element(int *arr, int from, int to)
{
    int x = arr[from];

    for (int i = from; i > to; i--)
    {
        arr[i] = arr[i-1];
    }
    arr[to] = x;
}
