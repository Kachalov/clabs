#include <inttypes.h>
#include <string.h>
#include <stdio.h>

#include "mtrx.h"
#include "errors.h"

// TODO: Error handling
int main(int argc, char *argv[])
{
    int err = EOK;

    if (argc - 1 == 4)
    {
        mtrxp_t a = NULL;
        mtrxp_t b = NULL;
        mtrxp_t c = NULL;

        err = read_mtrx(argv[2], &a);
        err = read_mtrx(argv[3], &b);

        if (strcmp(argv[1], "sub") == 0)
        {
            err = sum_mtrx(a, b, &c);
        }
        else if (strcmp(argv[1], "mul") == 0)
        {
            err = mul_mtrx(a, b, &c);
        }

        err = fprint_mtrx(c, argv[4]);

        free_mtrx(&a);
        free_mtrx(&b);
        free_mtrx(&c);
    }
    else if (argc - 1 == 2)
    {
        mtrxp_t a = NULL;
        mtrxp_t c = NULL;

        err = read_mtrx(argv[1], &a);

        err = slae_mtrx(a, &c);

        err = fprint_mtrx(c, argv[2]);

        free_mtrx(&a);
        free_mtrx(&c);
    }
    printf("Err code: %d\n", err);

    return 0;
}
