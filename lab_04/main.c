#include <stdio.h>
#include <string.h>
#include <assert.h>

#define ARRAY_MAX 10
// 2x array size in case 4 (adding elements to array)
#define ARRAY_SIZE (ARRAY_MAX<<1)

#define STR_SIZE 80

#define OK 0
#define ERR_INVALID_DATA 1
#define ERR_ARRAY_SIZE 2
#define ERR_ARRAY_INDEX 3
#define ERR_NO_DATA 4
#define ERR_NOT_ENOUGH_DATA 5

typedef int (*array_function_t)(int *, int);
typedef int (*array_mutable_function_t)(int *, int *);

int read_array(int *arr, int *arr_size);
void print_array(const int *arr, int arr_size);
void print_error(int err, char *err_fun_name);

/**
 * @brief Get function name by code.
 * @param err_function Error code
 * @param functions_names Array of functions' names
 * @param names_size Size of `functions_names`
 * @return Function name
 */
char *get_function_name(int err_function, char (*functions_names)[STR_SIZE],
                        int names_size);

/**
 * @brief Insert element into `arr`.
 * @param arr Array
 * @param arr_size Array size
 * @param element Element to insert
 * @param pos Position
 * @return status
 */
int array_insert_element(int *arr, int *arr_size, int element, int pos);

int sort_range(int *arr, int begin, int end);

int sum_mul_wrapper(int *arr, int arr_size);
int sum_mul(const int *arr, int arr_size, int *sum, int *mul);

int copy_avg_wrapper(int *arr, int arr_size);
int copy_avg(const int *arr, int arr_size,
             int **arr_dest, int *arr_dest_size);

int add_sum_wrapper(int *arr, int *arr_size);
int add_sum(int *arr, int *arr_size, int x);

int del_negative(int *arr, int *arr_size);
int swap(int *arr, int arr_size);
int replace_max(int *arr, int arr_size);
int sort_min_max(int *arr, int arr_size);

int main(void)
{
    int arr[ARRAY_SIZE] = {0};
    int arr_size = 0;

    int arr_tmp[ARRAY_SIZE] = {0};
    int arr_tmp_size = 0;

    int err = OK;
    int err_function = -1;

    array_function_t funs[] =
    {
        &sum_mul_wrapper,
        &copy_avg_wrapper,
        &swap,
        &replace_max,
        &sort_min_max,
    };
    array_mutable_function_t funs_mutable[] =
    {
        &del_negative,
        &add_sum_wrapper,
    };

    char funs_names[][STR_SIZE] =
    {
        "sum_mul",
        "copy_avg",
        "swap",
        "replace_max",
        "sort_min_max",
        "del_negative",
        "add_sum",
    };
    int names_size = sizeof(funs_names)/STR_SIZE;

    if((err = read_array(arr, &arr_size)) != OK)
        goto fail;

    // Arrays \w fixed size
    for (int i = 0; i < sizeof(funs)/sizeof(array_function_t); i++)
    {
        err_function++;
        memcpy(arr_tmp, arr, sizeof(arr));
        arr_tmp_size = arr_size;
        if ((err = (*funs[i])(arr_tmp, arr_tmp_size)) != OK)
        {
            print_error(err, get_function_name(
                    err_function, funs_names, names_size));
        }
        else
        {
            printf("Function '%s' array(%d): ", get_function_name(
                    err_function, funs_names, names_size), arr_tmp_size);
            print_array(arr_tmp, arr_tmp_size);
        }
    }

    // Arrays \w changeable size
    for (int i = 0;
         i < sizeof(funs_mutable)/sizeof(array_mutable_function_t); i++)
    {
        err_function++;
        memcpy(arr_tmp, arr, sizeof(arr));
        arr_tmp_size = arr_size;
        if ((err = (*funs_mutable[i])(arr_tmp, &arr_tmp_size)) != OK)
        {
            print_error(err, get_function_name(
                    err_function, funs_names, names_size));
        }
        else
        {
            printf("Function '%s' array(%d): ", get_function_name(
                    err_function, funs_names, names_size), arr_tmp_size);
            print_array(arr_tmp, arr_tmp_size);
        }
    }

    // Clean up last error
    err = OK;

    fail:
    if (err)
        print_error(err, get_function_name(
                err_function, funs_names, names_size));
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

void print_array(const int *arr, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

char *get_function_name(int err_function, char (*functions_names)[STR_SIZE],
                        int names_size)
{
    // Using `static` to prevent destroying string out of function context.
    static char err_fun_name[STR_SIZE] = "";

    if (err_function < 0 || err_function >= names_size)
        sprintf(err_fun_name, "#%d", err_function);
    else{
        memcpy(err_fun_name, functions_names[err_function],
               strlen(functions_names[err_function])+1);
    }

    return err_fun_name;
}

void print_error(int err, char *err_fun_name)
{
    char err_msg[STR_SIZE] = "";

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
            memcpy(err_msg, "no data", sizeof(err_msg));
            break;

        case ERR_NOT_ENOUGH_DATA:
            memcpy(err_msg, "not enough data", sizeof(err_msg));
            break;

        case ERR_ARRAY_INDEX:
            memcpy(err_msg, "invalid array index", sizeof(err_msg));
            break;

        default:
            sprintf(err_msg, "#%d", err);
    }

    fprintf(stderr, "Error: '%s'; In function: '%s'\n",
            err_msg, err_fun_name);
}

int sum_mul_wrapper(int *arr, int arr_size)
{
    int err = OK;
    int sum = 0;
    int mul = 0;

    if ((err = sum_mul(arr, arr_size, &sum, &mul)) == OK)
        printf("Sum: %d; Mul: %d;\n", sum, mul);

    return err;
}

int sum_mul(const int *arr, int arr_size, int *sum, int *mul)
{
    int elements_found = 0;

    *sum = 0;
    *mul = 1;

    for (int i = 0; i < arr_size; i++)
    {
        if (arr[i] % 2)
        {
            *mul *= arr[i];
            elements_found |= 2<<0;
        }
        else
        {
            *sum += arr[i];
            elements_found |= 2<<1;
        }
    }

    return elements_found == (2<<2) - 1 ? OK : ERR_NOT_ENOUGH_DATA;
}

int copy_avg_wrapper(int *arr, int arr_size)
{
    int err = OK;
    int *arr_dest = NULL;
    int arr_dest_size = 0;

    if ((err = copy_avg(arr, arr_size, &arr_dest, &arr_dest_size)) == OK)
        print_array(arr_dest, arr_dest_size);

    return err;
}

int copy_avg(const int *arr, int arr_size,
             int **arr_new, int *arr_dest_size)
{
    assert(arr_new != NULL);
    assert(arr_dest_size != NULL);

    float avg = 0;
    int arr_dest[ARRAY_SIZE] = {0};

    *arr_dest_size = 0;

    if (!arr_size)
        return ERR_NO_DATA;

    for (int i = 0; i < arr_size; i++)
        avg += arr[i];
    avg /= arr_size;

    for (int i = 0; i < arr_size; i++)
        if (arr[i] > avg)
            arr_dest[(*arr_dest_size)++] = arr[i];

    *arr_new = arr_dest;

    return OK;
}

int del_negative(int *arr, int *arr_size)
{
    int offset = 0;

    // In case there is only one element in array. It is a little bit
    // more complicated algorithm to look on next elements in array, so
    // I'm looking on previous elements.
    if (*arr_size == 1 && arr[0] < 0)
    {
        (*arr_size)--;
        arr[0] = 0;
    }

    for (int i = 1; i < *arr_size; i++)
    {
        arr[i - offset] = arr[i];

        if (arr[i - 1 - offset] >= 0)
            continue;

        arr[i - ++offset] = arr[i];
        arr[i] = 0;
    }
    *arr_size -= offset;

    return OK;
}


int add_sum_wrapper(int *arr, int *arr_size)
{
    int err = OK;
    int x = 0;

    printf("Enter x: ");
    if (scanf("%d", &x) != 1)
        return ERR_NO_DATA;

    err = add_sum(arr, arr_size, x);
    return err;
}

int add_sum(int *arr, int *arr_size, int x)
{
    int err = OK;
    int sum = 0;

    for (int i = 0; i < *arr_size; i++)
    {
        sum += arr[i];

        if (arr[i] != x)
            continue;

        if((err = array_insert_element(
                arr, arr_size, sum - arr[i], i + 1)) != OK)
            break;

        // Skip next element, because it's a sum.
        i++;
    }

    return err;
}

int swap(int *arr, int arr_size)
{
    int odd_ndx = -1;
    int even_ndx = -1;
    int tmp = 0;

    for (int i = 0; i < arr_size; i++)
    {
        if (arr[i] % 2 &&
                (odd_ndx == -1 || arr[odd_ndx] > arr[i]))
            odd_ndx = i;
        else if (!(arr[i] % 2) &&
                ((even_ndx == -1 || arr[even_ndx] < arr[i])))
            even_ndx = i;
    }

    if (odd_ndx == -1 || even_ndx == -1)
        return ERR_NO_DATA;

    tmp = arr[odd_ndx];
    arr[odd_ndx] = arr[even_ndx];
    arr[even_ndx] = tmp;

    return OK;
}

int replace_max(int *arr, int arr_size)
{
    int max_ndx = -1;
    int sum = 0;

    for (int i = 0; i < arr_size; i++)
    {
        if (arr[i] % 10 == 3)
            sum += arr[i];

        if (arr[i] % 3 == 0 && (max_ndx == -1 || arr[max_ndx] < arr[i]))
            max_ndx = i;
    }

    if (max_ndx == -1)
        return ERR_NO_DATA;

    arr[max_ndx] = sum;

    return OK;
}

int sort_min_max(int *arr, int arr_size)
{
    int err = OK;

    int min_ndx = 0;
    int max_ndx = 0;

    for (int i = 0; i < arr_size; i++)
    {
        if (arr[min_ndx] > arr[i])
            min_ndx = i;

        if (arr[max_ndx] < arr[i])
            max_ndx = i;
    }

    if (arr_size)
    {
        if (min_ndx < max_ndx)
            err = sort_range(arr, min_ndx, max_ndx);
        else
            err = sort_range(arr, max_ndx, min_ndx);
    }

    return err;
}

int array_insert_element(int *arr, int *arr_size, int element, int pos)
{
    assert(pos >= 0);

    if (*arr_size >= ARRAY_SIZE)
        return ERR_ARRAY_SIZE;

    if (pos >= *arr_size + 1)
        return ERR_ARRAY_INDEX;

    for (int i = (*arr_size)++ - 1; i >= pos; i--)
        arr[i + 1] = arr[i];

    arr[pos] = element;

    return OK;
}

int sort_range(int *arr, int begin, int end)
{
    int tmp = 0;

    for (int i = begin; i <= end - 1; i++)
    {
        for (int j = i; j <= end; j++)
        {
            if (arr[i] > arr[j])
            {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }

    return OK;
}
