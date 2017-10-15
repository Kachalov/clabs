#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "mtrx.h"
#include "errors.h"

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

int sum_mtrx(mtrxp_t a, mtrxp_t b, mtrxp_t *c_p)
{
    int err = EOK;

    if (a->m != b->m || a->n != b->n)
    {
        err = EMTRXSIZE;
    }
    else
    {
        err = alloc_mtrx(a->m, a->m, c_p, NULL);
        if (err == EOK)
        {
            for (int i = 0; i < a->m; i++)
                for (int j = 0; j < a->n; j++)
                    (*c_p)->d[i][j] = a->d[i][j] + b->d[i][j];
        }
    }

    return err;
}

int mul_mtrx(mtrxp_t a, mtrxp_t b, mtrxp_t *c_p)
{
    int err = EOK;

    return err;
}

int slae_mtrx(mtrxp_t a, mtrxp_t b, mtrxp_t *c_p)
{
    return EOK;
}
