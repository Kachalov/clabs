#include <inttypes.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "mtrx.h"
#include "mtrx_apply.h"
#include "errors.h"

int alloc_mtrx(mtrx_size_t m, mtrx_size_t n, mtrxp_t *mtrx_pp,
               apply_mtrx_f_t f, void *arg)
{
    assert(*mtrx_pp == NULL);
    assert(m != 0 || n != 0);

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
            (*mtrx_pp)->d[i][j] = f != NULL ? f(*mtrx_pp, i, j, arg) : 0;
    }

    return EOK;
}

int free_mtrx(mtrxp_t *mtrx_pp)
{
    if (*mtrx_pp != NULL)
    {
        free(*mtrx_pp);
        *mtrx_pp = NULL;
    }
    return EOK;
}

void apply_mtrx(mtrxp_t mtrx_p, apply_mtrx_f_t f, void *arg)
{
    for (int i = 0; i < mtrx_p->m; i++)
        for (int j = 0; j < mtrx_p->n; j++)
            mtrx_p->d[i][j] = f(mtrx_p, i, j, arg);
}

void sprint_mtrx(mtrxp_t mtrx_p, char *str)
{
    assert(str != NULL);

    if (mtrx_p == NULL)
        return;

    sprintf(str, "");
    for (int i = 0; i < mtrx_p->m; i++)
    {
        for (int j = 0; j < mtrx_p->n; j++)
            sprintf(str + strlen(str), "%.3f ", mtrx_p->d[i][j]);
        sprintf(str + strlen(str), "\n");
    }
}

void print_mtrx(mtrxp_t mtrx_p)
{
    char buf[4096];
    sprint_mtrx(mtrx_p, buf);
    printf("%s", buf);
}

int fprint_mtrx(mtrxp_t mtrx_p, char *fn)
{
    assert(fn != NULL);

    char buf[4096];
    int err = EOK;
    FILE *f = NULL;

    f = fopen(fn, "w");
    if (f == NULL)
        err = ENOFILE;

    if (err == EOK)
    {
        sprint_mtrx(mtrx_p, buf);
        fprintf(f, "%s", buf);
        fclose(f);
    }

    return err;
}

int sum_mtrx(mtrxp_t a, mtrxp_t b, mtrxp_t *c_p)
{
    assert(a != NULL);
    assert(b != NULL);

    int err = EOK;

    if (a->m != b->m || a->n != b->n)
    {
        err = EMTRXSIZE;
    }
    else
    {
        err = alloc_mtrx(a->m, a->n, c_p, NULL, NULL);
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
    assert(a != NULL);
    assert(b != NULL);

    int err = EOK;

    if (a->n != b->m)
    {
        err = EMTRXSIZE;
    }
    else
    {
        err = alloc_mtrx(a->m, b->n, c_p, NULL, NULL);
        if (err == EOK)
        {
            for (int i = 0; i < a->m; i++)
                for (int j = 0; j < b->n; j++)
                    (*c_p)->d[i][j] = mul_i_mtrx(a, b, i, j);
        }
    }

    return err;
}

mtrx_data_i_t mul_i_mtrx(mtrxp_t a, mtrxp_t b, mtrx_size_t i, mtrx_size_t j)
{
    mtrx_data_i_t r = 0;
    for (int k = 0; k < a->n; k++)
        r += a->d[i][k] * b->d[k][j];
    return r;
}

int slae_mtrx(mtrxp_t ac, mtrxp_t *c_p)
{
    assert(ac != NULL);

    int err = EOK;

    if (ac->n != ac->m + 1)
    {
        err = EMTRXSIZE;
    }
    else
    {
        mtrxp_t a = NULL;
        err = alloc_mtrx(ac->m, ac->n, &a, apply_mtrx_copy, ac);
        if (err == EOK)
        {
            err = alloc_mtrx(a->m, 1, c_p, NULL, NULL);
            if (err == EOK)
            {
                mtrxp_t b = NULL;
                err = alloc_mtrx(1, a->m, &b, NULL, NULL);
                if (err == EOK)
                {
                    err = gauss_mtrx(a, *c_p);
                }
                free_mtrx(&b);
            }
        }
        free_mtrx(&a);
    }

    return err;
}

int gauss_mtrx(mtrxp_t a, mtrxp_t c)
{
    int err = EOK;

    mtrxp_t k = NULL;
    err = alloc_mtrx(2, a->m, &k, apply_mtrx_ndx, NULL);
    if (err == EOK)
    {
        mtrx_data_i_t *b = k->d[1];
        mtrx_data_i_t *pos = k->d[0];
        mtrx_size_t j;
        mtrx_data_i_t tmp;

        for (int i = 0; i < a->m; i++)
        {
            j = max_el_row_mtrx(a, i);
            printf("max(%d): %.2f\n", j, a->d[i][j]);
            *(b++) = a->d[i][j];

            swap_col_mtrx(a, i, j);
            tmp = pos[i];
            pos[i] = pos[j];
            pos[j] = tmp;

            normalize_mtrx(a, i);
            printf("=====\n");
            print_mtrx(k);
            printf("-----\n");
            print_mtrx(a);
            printf("=====\n");
        }
        b = k->d[1];

        for (int i = a->m - 1; i >= 0; i--)
        {
            tmp = a->d[i][a->n - 1];
            for (int j = a->n - 2; j > i; j--)
            {
                printf("j: %d xi: %.3f bi: %.3f\n", j, a->d[i][j], b[(int)pos[j]]);
                tmp -= a->d[i][j] * b[(int)pos[j]];
            }
            c->d[i][0] = tmp / a->d[i][i];
        }

        printf("result:\n");
        print_mtrx(a);
        printf("solving:\n");
        print_mtrx(c);
        printf("bi and pos:\n");
        print_mtrx(k);
        free_mtrx(&k);
    }

    return err;
}

mtrx_size_t max_el_row_mtrx(mtrxp_t a, mtrx_size_t i)
{
    mtrx_size_t max_i = 0;
    for (mtrx_size_t j = 0; j < a->m; j++)
        if (fabs(a->d[i][j]) > fabs(a->d[i][max_i]))
            max_i = j;
    return max_i;
}

void swap_col_mtrx(mtrxp_t a, mtrx_size_t i, mtrx_size_t j)
{
    mtrx_data_i_t tmp;
    for (int k = 0; k < a->m; k++)
    {
        tmp = a->d[k][i];
        a->d[k][i] = a->d[k][j];
        a->d[k][j] = tmp;
    }
}

void normalize_mtrx(mtrxp_t a, mtrx_size_t from)
{
    mtrx_data_i_t d;
    for (int i = from; i < a->m; i++)
    {
        d = a->d[i][from];
        for (int j = 0; j < a->n; j++)
        {
            if (fabs(d) < 1e-7)
                continue;
            a->d[i][j] /= d;
        }
    }

    for (int j = 0; j < a->n; j++)
    {
        for (int i = from + 1; i < a->m; i++)
            a->d[i][j] -= a->d[from][j];
    }
}

mtrx_sizes_t size_file_mtrx(FILE *f)
{
    mtrx_sizes_t ss;
    ss.m = 0;
    ss.n = 0;
    mtrx_data_i_t tmp = 0;
    char c;
    int i = 0;
    fpos_t pos;

    fgetpos(f, &pos);
    while (!feof(f))
    {
        if ((c = fgetc(f)) == '\n')
        {
            ss.m++;
            i = 0;
        }
        else
        {
            ungetc(c, f);
            if (fscanf(f, "%f", &tmp) == 1)
            {
                ss.n = ++i > ss.n ? i : ss.n;
            }
            else
            {
                if (feof(f))
                    break;

                // EFORMAT case
                ss.m = 1;
                ss.n = 0;
                break;
            }
        }
    }

    fsetpos(f, &pos);
    return ss;
}

int read_mtrx(char *fn, mtrxp_t *m)
{
    int err = EOK;
    FILE *f = fopen(fn, "r");
    if (f == NULL)
        err = ENOFILE;

    if (err == EOK)
    {
        mtrx_sizes_t ss = size_file_mtrx(f);
        if (ss.m == 0 && ss.n == 0)
        {
            err = ENODATA;
        }
        else if ((ss.m == 1) ^ (ss.n == 1))
        {
            err = EFORMAT;
        }
        else
        {
            err = alloc_mtrx(ss.m, ss.n, m, NULL, NULL);

            ss.m = 0;
            ss.n = 0;
            char c;
            mtrx_data_i_t tmp = 0;

            if (err == EOK)
            {
                while (!feof(f))
                {
                    if ((c = fgetc(f)) == '\n')
                    {
                        ss.m++;
                        ss.n = 0;
                    }
                    else
                    {
                        ungetc(c, f);
                        if (fscanf(f, "%f", &tmp) == 1)
                        {
                            (*m)->d[ss.m][ss.n++] = tmp;
                        }
                        else
                        {
                            if (!feof(f))
                            {
                                free_mtrx(m);
                                err = EFORMAT;
                            }
                            break;
                        }
                    }
                }
            }
        }
        fclose(f);
    }

    return err;
}
