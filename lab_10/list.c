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
    for (; cur && cur != before; prev = cur, cur = cur->next);

    if (cur)
    {
        elem->next = cur->next;
        cur->next = elem;
    }
    else if (!before && prev)
    {
        prev->next = elem;
    }
    else if (!before)
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

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    return NULL;
}

void sorted_insert(node_t **head, node_t *element,
                   int (*comparator)(const void *, const void *))
{

}