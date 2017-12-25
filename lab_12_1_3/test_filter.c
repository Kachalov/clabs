#include <stdio.h>
#include <string.h>

#include "filter.h"
#include "array.h"
#include "test.h"
#include "errors.h"

int test_filter(void)
{
    int failed = 0;
    int err = 0;

    int res[100] = {};
    void *res_b = (void *)res;
    void *res_e = (void *)res;

    int test1[] = {};
    int *test1_e = (int *)&test1;
    int ex1[] = {};

    err = error(filter(test1, test1_e, &res_b, &res_e), "empty");
    if (err || (err = error(cmp_res(res_b, ex1, res_e - res_b), "empty")) != OK)
        failed++;

    int test2[] = {100, -50, 1, 30, 2, 3, 4};
    int *test2_e = (int *)&test2 + 7;
    int ex2[] = {100, -50};

    err = error(filter(test2, test2_e, &res_b, &res_e), "one negative");
    if (err || (err = error(cmp_res(res_b, ex2, res_e - res_b), "one negative")) != OK)
        failed++;

    int test3[] = {100, -50, 1, 30, -1, 3, 4};
    int *test3_e = (int *)&test3 + 7;
    int ex3[] = {100, -50, 1, 30, -1};

    err = error(filter(test3, test3_e, &res_b, &res_e), "two negatives");
    if (err || (err = error(cmp_res(res_b, ex3, res_e - res_b), "two negatives")) != OK)
        failed++;

    int test4[] = {100, 50, 1, 30, 1, 3, 4};
    int *test4_e = (int *)&test4 + 7;
    int ex4[] = {100, 50, 1, 30, 1, 3, 4};

    err = error(filter(test4, test4_e, &res_b, &res_e), "no negatives");
    if (err || (err = error(cmp_res(res_b, ex4, res_e - res_b), "no negatives")) != OK)
        failed++;

    return failed;
}
