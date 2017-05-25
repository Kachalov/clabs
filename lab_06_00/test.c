#include <stdio.h>
#include "errors.h"
#include "search.h"
#include "io.h"

typedef struct
{
    int arr[ARRAY_SIZE];
    int size;
    int max;
    int err;
} test_find_max_t;

int test_find_max();

int main(void)
{
    test_find_max_t tests[] = {
            {{1, 2, 3, 4}, 4, 5, OK},
            {{2}, 1, 4, OK},
            {{1, 2, 3, 4, 5}, 5, 6, OK},
            {{}, 0, 0, ERR_NO_DATA},
            {{4, 5, 6}, ARRAY_SIZE, 6, OK},
    };
    int max = 0;
    int errs = 0;
    int err = OK;

    for (int i = 0; i < sizeof(tests)/ sizeof(test_find_max_t); i++)
    {
        max = 0;
        if ((err = find_max(tests[i].arr,
                            tests[i].size, &max) != tests[i].err))
        {
            errs++;
            printf("E");
            continue;
        }

        if (max != tests[i].max)
        {
            errs++;
            printf("R");
            continue;
        }

        printf(".");
    }
    printf("\n");

    if (errs)
    {
        printf("ERRORS: %d\n", errs);
        return 1;
    }
    else
    {
        printf("OK\n");
        return 0;
    }
}
