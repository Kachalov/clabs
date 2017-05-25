#include <stdio.h>
#include "errors.h"
#include "search.h"
#include "io.h"

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
