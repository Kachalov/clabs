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
        if (err == EOK)
        {
            if (err == EOK)
            {
                err = read_mtrx(argv[3], &b);

                if (strcmp(argv[1], "sum") == 0)
                {
                    err = sum_mtrx(a, b, &c);
                }
                else if (strcmp(argv[1], "mul") == 0)
                {
                    err = mul_mtrx(a, b, &c);
                }

                if (err == EOK)
                {
                    err = fprint_mtrx(c, argv[4]);

                    printf("A mtrx:\n");
                    print_mtrx(a);
                    printf("\nB mtrx:\n");
                    print_mtrx(b);
                    printf("\nResult:\n");
                    print_mtrx(c);
                    printf("\n");
                }
            }
        }

        free_mtrx(&a);
        free_mtrx(&b);
        free_mtrx(&c);
    }
    else if (argc - 1 == 2)
    {
        mtrxp_t a = NULL;
        mtrxp_t c = NULL;

        err = read_mtrx(argv[1], &a);
        if (err == EOK)
        {
            printf("SLAE mtrx:\n");
            print_mtrx(a);
            printf("\n");

            err = slae_mtrx(a, &c);
            if (err == EOK)
            {
                mtrxp_t r = NULL;
                a->n--;

                printf("Result:\n");
                print_mtrx(c);
                printf("\n");

                err = mul_mtrx(a, c, &r);
                a->n++;
                if (err == EOK)
                {
                    printf("Checking A*X=Y:\n");
                    print_mtrx(r);
                    printf("\n");
                }
                free_mtrx(&r);
                err = fprint_mtrx(c, argv[2]);
            }
            else if (err == ENOSOLVING)
            {
                err = fprint_mtrx(c, argv[2]);
                printf("No solving!\n");
            }
        }

        free_mtrx(&a);
        free_mtrx(&c);
    }
    printf("Err code: %d\n", err);

    return err != EOK;
}
