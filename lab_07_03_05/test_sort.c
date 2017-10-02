#include <stdio.h>
#include <string.h>

#include "sort.h"
#include "array.h"
#include "test.h"
#include "errors.h"

int test_sort(void)
{
    int failed = 0;
    int err = 0;

    int res[100] = {};
    void *res_b = (void *)res;
    void *res_e = (void *)res;

    int test1[] = {};
    int ex1[] = {};

    sort(&test1, 0, sizeof(int), cmp_int);
    if (err || (err = error(cmp_res(res_b, ex1, res_e - res_b), "empty")) != OK)
        failed++;

    int test2[] = {100, -50, 1, 30, 2, 3, 4};
    int ex2[] = {100, -50};

    sort(&test2, 0, sizeof(int), cmp_int);
    if (err || (err = error(cmp_res(res_b, ex2, res_e - res_b), "full")) != OK)
        failed++;

    return failed;
}
