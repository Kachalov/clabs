#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dlfcn.h>

#include "errors.h"

int main(int argc, char *argv[]) {
    int err = OK;

    FILE *fin = NULL;
    FILE *fout = NULL;

    void *libarr;
    int (*process)(FILE *, FILE *, int);

    char **cur_arg = argv + 1;
    bool filtering = false;

    if (argc < 3)
    {
        err = NO_FILENAME;
    }
    else
    {
        if (strcmp(cur_arg[0], "-") == 0)
        {
            cur_arg++;
            filtering = true;
        }

        fin = fopen(cur_arg[0], "r");
        if (fin == NULL)
        {
            err = NO_FILE;
        }
        else
        {

            fout = fopen(cur_arg[1], "w");
            if (fout == NULL)
            {
                err = NO_FILE;
            }
            else
            {
                if (!(libarr = dlopen("./libarr.so", RTLD_LAZY)))
                {
                    printf("DL error: %s\n", dlerror());
                    err = DL_ERROR;
                }
                else if (!(process = dlsym(libarr, "process")))
                {
                    printf("DL error: %s\n", dlerror());
                    err = DL_ERROR;
                }
                else
                {
                    err = process(fin, fout, filtering);
                    fclose(fout);
                }

                if (libarr)
                    dlclose(libarr);
            }
            fclose(fin);
        }
    }

    if (err != 0)
    {
        printf("Error: %s\n", error_msg(err));
        return 1;
    }
    return 0;
}
