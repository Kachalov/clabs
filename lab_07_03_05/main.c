#include <stdio.h>

#define OK 0
#define NO_FILENAME 1
#define NO_FILE 2
#define FSEEK_ERROR 3
#define MEM_ALLOC_ERR 4

typedef int (*cmp_f_t)(const void *, const void *);

int get_data_len(FILE *fd, size_t size, size_t *data_len);
void sort(void *data, size_t num, size_t size, cmp_f_t);
int filter(void *data, size_t num,
           size_t size,
           cmp_f_t,
           void *data_new, size_t *num_new);

void print_array(const void *data, int num, int size);

int create_array_file(FILE *fd, size_t num, size_t size, void *data);
int create_array(size_t num, size_t size, void *data);
void delete_array(void *data);

int cmp_int(const void *a, const void *b);


int main(int argc, char *argv[])
{
    int err = 0;

    FILE *fin = NULL;
    FILE *fout = NULL;

    void *data = NULL;
    void *data_f = NULL;
    size_t data_size = sizeof(int);
    size_t data_len = 0;
    size_t data_f_len = 0;



    if (argc < 3)
    {
        err = NO_FILENAME;
        goto exit;
    }

    fin = fopen(argv[1], "w");
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

    if ((err = filter(&data, data_len, data_size, &cmp_int, &data_f, &data_f_len)) != OK)
        goto exit;

    sort(&data, data_len, data_size, &cmp_int);
    print_array(&data, data_len, data_size);

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
