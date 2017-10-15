#include <inttypes.h>
#include <string.h>
#include <stdio.h>

#include "mtrx.h"
#include "errors.h"

mtrx_data_i_t apply_mtrx_numerate(mtrxp_t mtrx_p, mtrx_size_t i, mtrx_size_t j)
{
    return mtrx_p->n * i + j;
}

mtrx_data_i_t apply_mtrx_e(mtrxp_t mtrx_p, mtrx_size_t i, mtrx_size_t j)
{
    return i == j;
}

int main(int argc, char *argv[])
{
    int err = EOK;

    mtrxp_t a = NULL;
    err = alloc_mtrx(10, 20, &a, apply_mtrx_e);
    printf("Err code: %d\n", err);

    mtrxp_t b = NULL;
    err = alloc_mtrx(20, 10, &b, apply_mtrx_numerate);
    printf("Err code: %d\n", err);

    mtrxp_t c = NULL;

    err = mul_mtrx(a, b, &c);
    print_mtrx(c);
    printf("Err code: %d\n", err);

    free_mtrx(&a);
    free_mtrx(&b);
    free_mtrx(&c);

    return 0;
}
