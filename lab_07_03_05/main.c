#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "filter.h"
#include "sort.h"
#include "errors.h"
#include "array.h"

// TODO: Use *begin and *end for array edges

int get_data_len(FILE *fd, size_t size, size_t *data_len);
unsigned long long tick(void);


int main(int argc, char *argv[])
{
    int err = OK;

    FILE *fin = NULL;
    FILE *fout = NULL;

    char **cur_arg = argv + 1;
    bool filtering = false;

    void *data = NULL;
    void *data_f = NULL;
    size_t data_size = sizeof(int);
    size_t data_len = 0;
    size_t data_f_len = 0;
    cmp_f_t cmp_f = cmp_int;

    if (argc < 3)
    {
        err = NO_FILENAME;
        goto exit;
    }

    if (strcmp(cur_arg[0], "-") == 0)
    {
        cur_arg++;
        filtering = true;
    }

    fin = fopen(cur_arg[0], "r");
    if (fin == NULL)
    {
        err = NO_FILE;
        goto exit;
    }

    fout = fopen(cur_arg[1], "w");
    if (fout == NULL)
    {
        err = NO_FILE;
        goto exit;
    }

    if ((err = get_data_len(fin, data_size, &data_len)) != OK)
        goto exit;

    if ((err = create_array_file(fin, data_len, data_size, &data)) != OK)
        goto exit;

    if (filtering)
    {
        if ((err = filter(data, data_len, data_size, cmp_f, &data_f, &data_f_len)) != OK)
            goto exit;
    }
    else
    {
        if ((err = create_array(data_len, data_size, &data_f)) != OK)
            goto exit;

        memcpy(data_f, data, data_len * data_size);
        data_f_len = data_len;
    }

    sort(data_f, data_f_len, data_size, cmp_f);
    print_array(fout, data_f, data_f_len, data_size);

    exit:

    if (data != NULL)
        delete_array(&data);

    if (data_f != NULL)
        delete_array(&data_f);

    if (fin != NULL)
        fclose(fin);

    if (fout != NULL)
        fclose(fout);

    if (err != 0)
    {
        printf("Error: %d\n", err);
        return 1;
    }
    return 0;
}

int get_data_len(FILE *fd, size_t size, size_t *data_len)
{
    *data_len = 0;
    int tmp;

    // To be sure we are in the beginning of a file
    fseek(fd, 0, SEEK_SET);

    while (fscanf(fd, "%d", &tmp) == 1)
        (*data_len)++;

    fseek(fd, 0, SEEK_SET);
    return OK;
}

unsigned long long tick(void)
{
    unsigned long long t;
    __asm__ __volatile__ ("rdtsc" : "=A" (t));
    return t;
}
