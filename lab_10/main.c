#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "debug.h"

int cmp_int(const void *a, const void *b)
{
    DPRINT("cmp(%d, %d) = %d", *(int *)a, *(int *)b, *(int *)a - *(int *)b);
    return *(int *)a - *(int *)b;
}

int main(int argc, char **argv)
{
    node_t *lst = NULL;
    node_t *el = NULL;
    int *tmp = NULL;

    for (int argi = 1; argi < argc; argi++)
    {
        if ((tmp = malloc(sizeof(int))))
        {
            if (sscanf(argv[argi], "%d", tmp) != 1)
                free(tmp);
            else
            {
                list_init(&el);
                el->data = tmp;
                insert(&lst, el, NULL);
            }
        }
    }

    printf("original: ");
    list_print_int(lst);

    printf("reversed: ");
    lst = reverse(lst);
    list_print_int(lst);

    printf("sorted: ");
    lst = sort(lst, cmp_int);
    list_print_int(lst);

    list_free(&lst);

    return 0;
}
