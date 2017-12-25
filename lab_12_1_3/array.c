#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "errors.h"
#include "sort.h"
#include "time.h"
#include "filter.h"

int process(FILE *fin, FILE *fout, int filtering)
{
    int err = OK;

    void *data_b = NULL;
    void *data_e = NULL;
    void *data_f_b = NULL;
    void *data_f_e = NULL;
    size_t data_size = sizeof(int);
    size_t data_len = 0;
    size_t data_f_len = 0;
    cmp_f_t cmp_f = cmp_int;

    unsigned long long tick_b, tick_e;

    if ((err = get_data_len(fin, data_size, &data_len)) == OK)
    {
        if ((err = create_array_file(fin, data_len, data_size, &data_b)) == OK)
        {
            data_e = (char *) data_b + data_size * data_len;

            if (filtering)
            {
                err = filter(data_b, data_e, &data_f_b, &data_f_e);
                data_f_len = (data_f_e - data_f_b) / data_size;
            }
            else
            {
                if ((err = create_array(data_len, data_size, &data_f_b)) == OK)
                {
                    memcpy(data_f_b, data_b, data_len * data_size);
                    data_f_len = data_len;
                    data_f_e = (char *) data_f_b + data_size * data_f_len;
                }
            }

            if (err == OK)
            {
                tick_b = tick();
                sort(data_f_b, data_f_len, data_size, cmp_f);
                tick_e = tick();
                print_int_array(fout, data_f_b, data_f_e);
                printf("%llu\n", tick_e - tick_b);
            }
        }
    }

    if (data_b != NULL)
    {
        free(data_b);
        data_b = NULL;
        delete_array(&data_b);
    }

    if (data_f_b != NULL)
    {
        free(data_f_b);
        data_f_b = NULL;
        delete_array(&data_f_b);
    }

    return err;
}

void print_int_array(FILE *fd, const void *b, const void *e)
{
    for(int *it = (int *)b; it < (int *)e; it++)
    {
        fprintf(fd, "%d ", *it);
    }
    fprintf(fd, "\n");
}

int create_array_file(FILE *fd, size_t num, size_t size, void **data)
{
    int err = OK;
    void *it = NULL;
    int tmp = 0;

    fseek(fd, 0, SEEK_SET);
    if ((err = create_array(num, size, data)) == OK)
    {
        it = *data;

        while (fscanf(fd, "%d", &tmp) == 1) {
            memcpy(it, &tmp, size);
            it = (char *) it + size;
        }

        fseek(fd, 0, SEEK_SET);
    }
    return err;
}

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
