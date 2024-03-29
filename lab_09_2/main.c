#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "mystr.h"

int process_data(FILE *fin, FILE *fout, char *search, char *replace);

int main(int argc, char **argv)
{
    FILE *fin = NULL;
    FILE *fout = NULL;
    int err = EOK;

    if (argc != 5)
    {
        err = EARGS;
    }
    else
    {
        fin = fopen(argv[1], "r");
        fout = fopen(argv[2], "w");

        if (fin == NULL || fout == NULL)
        {
            err = EIO;
        }
        else
        {
            err = process_data(fin, fout, argv[3], argv[4]);
        }

        if (fin != NULL)
        {
            fclose(fin);
        }

        if (fout != NULL)
        {
            fclose(fout);
        }
    }

    if (err != EOK)
        printf("Error code: %d\n", err);

    return err != EOK;
}

int process_data(FILE *fin, FILE *fout, char *search, char *replace)
{
    char *l = NULL;
    char *r = NULL;
    size_t n = 0;
    int err = EOK;

    do
    {
        my_getline(&l, &n, fin);

        if (n != -1)
        {
            r = my_str_replace(l, search, replace);
            printf("|%s|\n", r);
            fputs(r, fout);
            fputs("\n", fout);
        }

        if (l != NULL)
        {
            free(l);
            l = NULL;
        }

        if (r != NULL)
        {
            free(r);
            r = NULL;
        }
    }
    while (n != EOF);

    return err;
}
