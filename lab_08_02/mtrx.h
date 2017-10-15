#pragma once

#include <inttypes.h>

typedef int32_t mtrx_data_i_t;
typedef mtrx_data_i_t **mtrx_data_t;
typedef uint32_t mtrx_size_t;
typedef struct _mtrx_t
{
    mtrx_size_t m;
    mtrx_size_t n;
    mtrx_data_t d;
} mtrx_t;

typedef mtrx_t *mtrxp_t;
typedef mtrx_data_i_t (*apply_mtrx_f_t)(mtrxp_t, mtrx_size_t, mtrx_size_t);

int alloc_mtrx(mtrx_size_t m, mtrx_size_t n, mtrxp_t *mtrx_pp, apply_mtrx_f_t f);
int free_mtrx(mtrxp_t *mtrx_pp);
void sprint_mtrx(mtrxp_t mtrx_p, char *str);
void print_mtrx(mtrxp_t mtrx_p);
int sum_mtrx(mtrxp_t a, mtrxp_t b, mtrxp_t *c_p);
int mul_mtrx(mtrxp_t a, mtrxp_t b, mtrxp_t *c_p);
int slae_mtrx(mtrxp_t a, mtrxp_t b, mtrxp_t *c_p);
