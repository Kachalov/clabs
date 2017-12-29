#include <stdlib.h>

#include "list.h"

int list_add(list1_t **head, void *data)
{
    int err = 0;

    list1_t *d = malloc(sizeof(list1_t));
    if (!d)
        err = 1;
    else
    {
        d->data = data;
        d->next = *head;
        *head = d;
    }

    return err;
}

void list_del(list1_t **head)
{
    list1_t *tmp = NULL;

    if (*head)
    {
        tmp = (*head)->next;
        free(*head);
        *head = tmp;
    }
}
