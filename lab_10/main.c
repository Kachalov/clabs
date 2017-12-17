#include <stdio.h>

#include "list.h"
#include "debug.h"

int cmp_int(const void *a, const void *b)
{
    DPRINT("cmp(%d, %d) = %d", *(int *)a, *(int *)b, *(int *)a - *(int *)b);
    return *(int *)a - *(int *)b;
}

int main(void)
{
    node_t *lst = NULL;
    node_t *el = NULL;
    node_t *tmp = NULL;

    int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    list_init(&el);
    el->data = data + 0;
    insert(&lst, el, NULL);

    list_init(&el);
    el->data = data + 5;
    insert(&lst, el, NULL);

    list_init(&el);
    el->data = data + 3;
    insert(&lst, el, NULL);
    tmp = el;

    list_init(&el);
    el->data = data + 9;
    insert(&lst, el, NULL);

    list_init(&el);
    el->data = data + 6;
    insert(&lst, el, tmp);

    list_print_int(lst);
    lst = reverse(lst);
    list_print_int(lst);
    lst = sort(lst, cmp_int);
    list_print_int(lst);

    list_free(&lst);

    return 0;
}
