#include <stdlib.h>
#include <stdint.h>

#include "list.h"
#include "debug.h"
#include "errors.h"

int list_init(node_t **head)
{
    int err = EOK;
    *head = malloc(sizeof(node_t));

    if (!*head)
        err = EOOM;
    else
    {
        (*head)->data = NULL;
        (*head)->next = NULL;
    }

    return err;
}

void list_free(node_t **head)
{
    while (pop_front(head));
}

void *pop_front(node_t **head)
{
    void *ret = NULL;
    node_t *tmp = NULL;

    if (*head)
    {
        ret = (*head)->data;
        tmp = (*head)->next;
        free(*head);
        *head = tmp;
    }

    return ret;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    node_t *cur = *head;
    node_t *prev = NULL;

    elem->next = NULL;

    for (; cur && cur != before; prev = cur, cur = cur->next);

    if (cur)
    {
        elem->next = cur->next;
        cur->next = elem;
    }
    else if (!before && prev) // End of non-empty list
    {
        prev->next = elem;
    }
    else if (!before) // Empty list
    {
        *head = elem;
    }
}

node_t *reverse(node_t *head)
{
    node_t *ret = NULL;
    node_t *cur = head;
    node_t *before = NULL;

    while (cur)
    {
        before = cur->next;
        cur->next = ret;
        ret = cur;
        cur = before;
    }

    return ret;
}

node_t *sort(node_t *head, int (*cmp)(const void *, const void *))
{
    node_t *ret = NULL;
    node_t *itn = NULL;

    for (node_t *it = head; it;)
    {
        itn = it->next;
        sorted_insert(&ret, it, cmp);
        #ifdef DEBUG
            DPRINT("list: ");
            list_print_int(ret);
        #endif
        it = itn;
    }

    return ret;
}

void sorted_insert(node_t **head, node_t *el,
                   int (*cmp)(const void *, const void *))
{
    node_t *prev = NULL;

    for (node_t *it = *head;
         it && cmp(it->data, el->data) <= 0;
         prev = it, it = it->next);

    DPRINT("sorted_insert:prev = %p", (void *)prev);

    if (*head && !prev)
    {
        el->next = *head;
        *head = el;
    }
    else
        insert(head, el, prev);
}
