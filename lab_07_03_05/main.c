#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define NO_FILENAME 1
#define NO_FILE 2
#define FSEEK_ERROR 3
#define MEM_ALLOC_ERR 4

typedef int (*cmp_f_t)(const void *, const void *);

int get_data_len(FILE *fd, size_t size, size_t *data_len);
void sort(void *data, size_t num, size_t size, cmp_f_t cmp_f);
int filter(void *data, size_t num,
           size_t size,
           cmp_f_t cmp_f,
           void **data_new, size_t *num_new);

void print_array(FILE *fd, const void *data, int num, int size);

int create_array_file(FILE *fd, size_t num, size_t size, void **data);
int create_array(size_t num, size_t size, void **data);
void delete_array(void **data);

int cmp_int(const void *a, const void *b);


int main(int argc, char *argv[])
{
    int err = OK;

    FILE *fin = NULL;
    FILE *fout = NULL;

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

    fin = fopen(argv[1], "r");
    if (fin == NULL)
    {
        err = NO_FILE;
        goto exit;
    }

    fout = fopen(argv[2], "w");
    if (fout == NULL)
    {
        err = NO_FILENAME;
        goto exit;
    }

    if ((err = get_data_len(fin, data_size, &data_len)) != OK)
        goto exit;

    if ((err = create_array_file(fin, data_len, data_size, &data)) != OK)
        goto exit;

    if ((err = filter(data, data_len, data_size, cmp_f, &data_f, &data_f_len)) != OK)
        goto exit;

    sort(data, data_len, data_size, cmp_f);
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

void sort(void *data, size_t num, size_t size, cmp_f_t cmp_f)
{
    // TODO: Implement
}

int filter(void *data, size_t num,
           size_t size,
           cmp_f_t cmp_f,
           void **data_new, size_t *num_new)
{
    int err = OK;

    // TODO: Implement

    if ((err = create_array(num, size, data_new)) != OK)
        return err;

    memcpy(*data_new, data, num * size);
    *num_new = num;

    return OK;
}

void print_array(FILE *fd, const void *data, int num, int size)
{
    char *it = (char *)data;

    for(int i = 0; i < num; i++)
    {
        int *x = (int *)it;
        printf("%d ", *x);
        fprintf(fd, "%d ", *it);
        it += size;
    }
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

int cmp_int(const void *a, const void *b)
{
    // TODO: Implement
    return OK;
}
