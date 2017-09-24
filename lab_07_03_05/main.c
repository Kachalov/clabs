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

    void *data_b = NULL;
    void *data_e = NULL;
    void *data_f_b = NULL;
    void *data_f_e = NULL;
    size_t data_size = sizeof(int);
    size_t data_len = 0;
    size_t data_f_len = 0;
    cmp_f_t cmp_f = cmp_int;

    unsigned long long tick_b, tick_e;

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

    if ((err = create_array_file(fin, data_len, data_size, &data_b)) != OK)
        goto exit;

    data_e = (char *)data_b + data_size * data_len;

    if (filtering)
    {
        if ((err = filter(data_b, data_e, &data_f_b, &data_f_e)) != OK)
            goto exit;
    }
    else
    {
        if ((err = create_array(data_len, data_size, &data_f_b)) != OK)
            goto exit;

        memcpy(data_f_b, data_b, data_len * data_size);
        data_f_len = data_len;
        data_f_e = (char *)data_f_b + data_size * data_f_len;
    }

    tick_b = tick();
    sort(data_f_b, data_f_len, data_size, cmp_f);
    tick_e = tick();
    print_int_array(fout, data_f_b, data_f_e);
    printf("%llu\n", tick_e - tick_b);

    exit:

    if (data_b != NULL)
        delete_array(&data_b);

    if (data_f_b != NULL)
        delete_array(&data_f_b);

    if (fin != NULL)
        fclose(fin);

    if (fout != NULL)
        fclose(fout);

    if (err != 0)
    {
        printf("Error: %s\n", error_msg(err));
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
