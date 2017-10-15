#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define error(err, err_no, label) {err = err_no; goto label;}
#define EOK 0
#define EOOM 1

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

mtrx_data_i_t apply_mtrx_numerate(mtrxp_t mtrx_p, mtrx_size_t i, mtrx_size_t j)
{
    return mtrx_p->n * i + j;
}

int alloc_mtrx(mtrx_size_t m, mtrx_size_t n, mtrxp_t *mtrx_pp, apply_mtrx_f_t f)
{
    *mtrx_pp = (mtrxp_t)malloc(sizeof(mtrx_t) +
                            m * sizeof(mtrx_data_i_t *) + m * n * sizeof(mtrx_data_i_t));

    if (*mtrx_pp == NULL)
        return EOOM;

    (*mtrx_pp)->d = (mtrx_data_t)((char *)(*mtrx_pp) + sizeof(mtrx_t));
    (*mtrx_pp)->n = n;
    (*mtrx_pp)->m = m;

    for (int i = 0; i < m; i++)
    {
        (*mtrx_pp)->d[i] = (mtrx_data_i_t *)&(*mtrx_pp)->d[m] + i * n;
        for (int j = 0; j < n; j++)
                (*mtrx_pp)->d[i][j] = f != NULL ? f(*mtrx_pp, i, j) : 0;
    }

    return EOK;
}

int free_mtrx(mtrxp_t *mtrx_pp)
{
    free(*mtrx_pp);
    *mtrx_pp = NULL;
    return EOK;
}

void sprint_mtrx(mtrxp_t mtrx_p, char *str)
{
    sprintf(str + strlen(str), "%d %d\n", mtrx_p->m, mtrx_p->n);
    for (int i = 0; i < mtrx_p->m; i++)
    {
        for (int j = 0; j < mtrx_p->n; j++)
            sprintf(str + strlen(str), "%d ", mtrx_p->d[i][j]);
        sprintf(str + strlen(str), "\n");
    }
}

void print_mtrx(mtrxp_t mtrx_p)
{
    char buf[4096];
    sprint_mtrx(mtrx_p, buf);
    printf("%s", buf);
}

int sum_mtrx(mtrx_t a, mtrxp_t b)
{
    return EOK;
}

int mul_mtrx(mtrx_t a, mtrxp_t b)
{
    return EOK;
}

int slae_mtrx(mtrx_t a, mtrxp_t b)
{
    return EOK;
}

int main(int argc, char *argv[])
{
    mtrxp_t mtrx_p = NULL;
    alloc_mtrx(10, 20, &mtrx_p, apply_mtrx_numerate);

    print_mtrx(mtrx_p);

    free_mtrx(&mtrx_p);
    return 0;
}
