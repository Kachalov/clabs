#include <stdio.h>
#include <string.h>

#define ARRAY_MAX 10
// 2x array size in case 4 (adding elements to array)
#define ARRAY_SIZE (ARRAY_MAX<<1)

#define OK 0
#define ERR_INVALID_DATA 1
#define ERR_ARRAY_SIZE 2
#define ERR_NO_DATA 3

typedef int (*array_function_t)(int *, int);

int read_array(int *arr, int *arr_size);
void print_array(int *const arr, int arr_size);
void print_error(int err, int err_function);

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
    int err_function = -1;
    array_function_t funs[] = {&sum_mul, &copy_avg, &del_negative, &add_sum, 
        &swap, &replace_max, &sort_min_max};

    if((err = read_array(arr, &arr_size)) != OK)
        goto fail;

    for (int i = 0; i < sizeof(funs)/sizeof(array_function_t); i++)
    {
        err_function = i + 1;
        if ((err = (*funs[i])(arr, arr_size)) != OK)
            print_error(err, err_function);
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

    if (*arr_size < 0)
        return ERR_INVALID_DATA;

    if (*arr_size > ARRAY_MAX)
        return ERR_ARRAY_SIZE;

    printf("Enter array: ");
    for (int i = 0; i < *arr_size; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            *arr_size = i;
            return ERR_INVALID_DATA;
        }
    }

    return OK;
}

void print_array(int *const arr, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void print_error(int err, int err_function)
{
    char err_msg[80] = "";

    switch (err)
    {
        case OK:
            return;

        case ERR_INVALID_DATA:
            memcpy(err_msg, "invalid data", sizeof(err_msg));
            break;

        case ERR_ARRAY_SIZE:
            memcpy(err_msg, "invalid array size", sizeof(err_msg));
            break;

        case ERR_NO_DATA:
            memcpy(err_msg, "empty array", sizeof(err_msg));
            break;

        default:
            sprintf(err_msg, "#%d", err);
    }

    fprintf(stderr, "Error: %s; In function: #%d\n", err_msg, err_function);
}

int sum_mul(int *const arr, int arr_size)
{
    int sum = 0;
    int mul = 1;

    for (int i = 0; i < arr_size; i++)
    {
        if (arr[i] % 2)
            mul *= arr[i];
        else
            sum += arr[i];
    }

    printf("Sum: %d; Mul: %d;\n", sum, mul);

    return OK;
}

int copy_avg(int *const arr, int arr_size)
{
    float avg = 0;
    int arr_dest[ARRAY_SIZE] = {0};
    int arr_dest_size = 0;

    if (!arr_size)
        return ERR_NO_DATA;

    for (int i = 0; i < arr_size; i++)
        avg += arr[i];
    avg /= arr_size;

    for (int i = 0; i < arr_size; i++)
        if (arr[i] > avg)
            arr_dest[arr_dest_size++] = arr[i];

    printf("Larger than average (%0.2f): ", avg);
    print_array(arr_dest, arr_dest_size);

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

