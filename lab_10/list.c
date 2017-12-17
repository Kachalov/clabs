#include <stdlib.h>
#include <stdint.h>

#include "list.h"
#include "debug.h"
#include "errors.h"

int list_init(node_t **list_ptr)
{
    node_t *list = malloc(sizeof(node_t));

    if (list == NULL)
    {
        return EOOM;
    }

    list->data = NULL;
    list->next = NULL;
    *list_ptr = list;

    return EOK;
}

void list_free(node_t **list_ptr)
{
    node_t *next = NULL;

    while (*list_ptr != NULL)
    {
        next = (*list_ptr)->next;
        free(*list_ptr);
        *list_ptr = next;
    }
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