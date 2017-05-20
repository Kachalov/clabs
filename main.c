#include <stdio.h>

#define ARRAY_MAX 10
// 2x array size in case 4 (adding elements in array)
#define ARRAY_SIZE (ARRAY_MAX<<1)

#define OK 0

typedef int (*array_function_t)(int *, int);

int read_array(int *arr, int *arr_size);
void print_array(int *const arr, int arr_size);
void print_error(int error);

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
		print_error(err);
	return err == OK ? 0 : 1;
}

int read_array(int *arr, int *arr_size)
{
	return OK;
}

void print_array(int *const arr, int arr_size)
{
	
}

void print_error(int error)
{
	
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

