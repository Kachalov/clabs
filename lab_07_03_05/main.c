#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
int filter_find_pos(int *begin, int *end);
int swap(void *a, void *b, size_t size);
unsigned long long tick(void);

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

void sort(void *data, size_t num, size_t size, cmp_f_t cmp_f)
{
    // TODO: Implement 6th algorithm

    if (num == 0)
        return;

    for (int i = 0; i < num - 1; i++)
        for (int j = i + 1; j < num; j++)
            if (cmp_f((char *)data + i * size, (char *)data + j * size) > 0)
                swap((void *)((char *)data + i * size), (void *)((char *)data + j * size), size);
}

int filter(void *data, size_t num,
           size_t size,
           cmp_f_t cmp_f,
           void **data_new, size_t *num_new)
{
    int err = OK;
    int p = 0;

    // TODO: Implement
    p = filter_find_pos((int *)data, (int *)data + num);
    printf("position: %d\n", p);

    if ((err = create_array(p, size, data_new)) != OK)
        return err;

    memcpy(*data_new, data, p * size);
    *num_new = p;

    return OK;
}

int filter_find_pos(int *begin, int *end)
{
    int pos = end - begin;
    int i = pos;

    for (int *it = end - 1; it >= begin; it--, i--)
    {
        printf("%d ", *it);
        if (*it < 0)
        {
            pos = i;
            break;
        }
    }

    return pos;
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

int swap(void *a, void *b, size_t size)
{
    void *tmp = NULL;
    int err = OK;

    if ((tmp = malloc(size)) == NULL)
        goto exit;

    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);

    exit:
    if (tmp != NULL)
        free(tmp);
    return err;
}

unsigned long long tick(void)
{
    unsigned long long t;
    __asm__ __volatile__ ("rdtsc" : "=A" (t));
    return t;
}

int cmp_int(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
