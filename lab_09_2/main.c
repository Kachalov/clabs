#include <stdio.h>
#include <stdlib.h>

#include "mystr.h"

int main(int argc, char **argv)
{
    FILE *f = fopen("Makefile", "r");
    char *l = NULL;
    size_t n = 0;

    do
    {
        my_getline(&l, &n, f);
        if (n != -1)
            printf("%zu '%s'\n", n, l);

        if (l != NULL)
        free(l);
    }
    while (n != -1);

    return 0;
}
