#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "test_filter.h"
#include "test_sort.h"
#include "errors.h"

int error(int err, char *test)
{
    if (err != OK)
        fprintf(stderr, "Failed %s: err %d\n", test, err);

    return err;
}

int cmp_res(int *test, int *res, int size)
{
    return memcmp(test, res, size) == 0 ? OK : -1;
}

int main(void)
{
    int failed = 0;

    failed += test_filter();
    failed += test_sort();

    printf("Total tests failed: %d\n", failed);

    return failed != 0;
}
