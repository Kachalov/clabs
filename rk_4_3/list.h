#pragma once

typedef struct _list1_t
{
    struct _list1_t *next;
    void *data;
} list1_t;

int list_add(list1_t **head, void *data);
void list_del(list1_t **head);
