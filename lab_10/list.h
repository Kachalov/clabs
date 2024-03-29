#pragma once

#define for_each(it, lst) for (node_t *it = (lst); it; it = it->next)
#define list_print_int(lst) do {\
    for_each(it, lst){\
        printf("%d", *(int *)it->data);\
        if (it->next) printf(" ");\
    }\
    printf("\n");\
} while(0)

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

int node_init(node_t **head);
void node_free(node_t **head);
void *pop_front(node_t **head);
void insert(node_t **head, node_t *elem, node_t *before);
int insert_data(node_t **head, void *data);
node_t *reverse(node_t *head);
node_t *sort(node_t *head, int (*comparator)(const void *, const void *));
void sorted_insert(node_t **head, node_t *element,
                   int (*comparator)(const void *, const void *));
