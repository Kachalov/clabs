#include <stdio.h>

#include "list.h"

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

    lst = reverse(lst);

    for_each(it, lst)
        printf("%d ", *(int *)it->data);
    printf("\n");

    list_free(&lst);

    return 0;
}
