#include <stdio.h>

#define ARRAY_MAX 10
// 2x array size in case 4 (adding elements in array)
#define ARRAY_SIZE (ARRAY_MAX<<1)

#define OK 0
#define ERR_INVALID_DATA 1
#define ERR_ARRAY_SIZE 2

typedef int (*array_function_t)(int *, int);

int read_array(int *arr, int *arr_size);
void print_array(int *const arr, int arr_size);
void print_error(int err, err_function);

int sum_mul(int *const arr, int arr_size);
int copy_avg(int *const arr, int arr_size);
int del_negative(int *const arr, int arr_size);
int add_sum(int *const arr, int arr_size);
int swap(int *const arr, int arr_size);
int replace_max(int *const arr, int arr_size);
int sort_min_max(int *const arr, int arr_size);

int main(void)
{
    int arr[ARRAY_SIZE] = {0};
    int arr_size = 0;
    int err = OK;
    int err_function = -2;
    array_function_t funs[] = {&sum_mul, &copy_avg, &del_negative, &add_sum, 
        &swap, &replace_max, &sort_min_max};

    read_array(arr, &arr_size);
    for (int i = 0; i < sizeof(funs)/sizeof(array_function_t); i++)
    {
        err_function = i + 1;
        if ((err = (*funs[i])(arr, arr_size)) != OK)
            goto fail;
    }

    fail:
    if (err)
        print_error(err, err_function);
    return err == OK ? 0 : 1;
}

int read_array(int *arr, int *arr_size)
{
    printf("Enter size of array: ");
    if (scanf("%d", arr_size) != 1)
        return ERR_INVALID_DATA;

    if (arr_size < 0)
        return ERR_INVALID_DATA;

    if (arr_size > ARRAY_MAX)
        return ERR_ARRAY_SIZE;

    return OK;
}

void print_array(int *const arr, int arr_size)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}

void print_error(int err, int err_function)
{
    fprintf(stderr, "Error #%d in function #%d", err, err_function);
}

int sum_mul(int *const arr, int arr_size)
{
    return OK;
}

int copy_avg(int *const arr, int arr_size)
{
    return OK;
}

int del_negative(int *const arr, int arr_size)
{
    return OK;
}

int add_sum(int *const arr, int arr_size)
{
    return OK;
}

int swap(int *const arr, int arr_size)
{
    return OK;
}

int replace_max(int *const arr, int arr_size)
{
    return OK;
}

int sort_min_max(int *const arr, int arr_size)
{
    return OK;
}

