#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#ifdef DEBUG
    #define DPRINT(...) {fprintf(stderr, "DEBUG: "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
    #define DPRINT(...)
#endif

#define ERR_NO 0
#define ERR_OOM 1

typedef struct list
{
    uint64_t num;
    uint8_t count;
    struct list *next;
} list_t;

uint8_t create_list(list_t **list);
uint8_t delete_list(list_t **list);
uint8_t add_element(list_t **list);
//uint8_t delete_element(list_t **list, list_t *element);
void print_list(list_t *list);

uint8_t decompose(uint64_t num, list_t **list);
void print_errcode(uint8_t err);

int main(void)
{
    uint64_t num;
    list_t *list = NULL;
    uint8_t err = ERR_NO;

    setbuf(stdout, NULL);

    printf("Enter number: ");
    if (scanf("%" SCNu64, &num) != 1)
    {
        printf("Input error\n");
        return 1;
    }

    err = decompose(num, &list);
    if (err)
    {
        print_errcode(err);
        return 1;
    }

    print_list(list);
    delete_list(&list);
    return 0;
}

uint8_t decompose(uint64_t num, list_t **list_ptr)
{
    uint8_t err = ERR_NO;
    list_t *list = NULL;

    for (uint64_t i = 2; i <= num; i++)
    {
        if (num % i)
            continue;

        err = add_element(&list);
        if (err)
            return err;

        list->num = i;
	    while ((num % i == 0) && (num >= 2))
        {
            list->count++;
            num /= i;
        }

        DPRINT("List address: %p->%p [%" PRIu64 "x%" PRIu8 "]",
               list, list->next, list->num, list->count);
    }

    *list_ptr = list;
    return ERR_NO;
}

void print_errcode(uint8_t err)
{
    switch (err)
    {
        case ERR_NO:
            break;
        case ERR_OOM:
            fprintf(stderr, "#%" PRIu8 " Can't allocate memory\n", err);
            break;
        default:
            fprintf(stderr, "#%" PRIu8 " Unknown error\n", err);
            break;
    }
}

uint8_t create_list(list_t **list)
{
    list_t *list_ptr = (list_t *) malloc(sizeof(list_t));

    if (list_ptr == NULL)
    {
        return ERR_OOM;
    }

    list_ptr->num = 0;
    list_ptr->count = 0;
    list_ptr->next = NULL;
    *list = list_ptr;

    return ERR_NO;
}

uint8_t delete_list(list_t **list)
{
    list_t *next = NULL;

    while (*list != NULL)
    {
        next = (*list)->next;
        free(*list);
        *list = next;
    }

    return ERR_NO;
}

uint8_t add_element(list_t **list)
{
    list_t *element = NULL;
    uint8_t err = ERR_NO;

    if (*list == NULL)
    {
        err = create_list(list);
        if (err)
            return err;
        return ERR_NO;
    }

    err = create_list(&element);
    if (err)
        return err;

    element->next = *list;
    *list = element;
    return ERR_NO;
}

//uint8_t delete_element(list_t **list, list_t *element);

void print_list(list_t *list)
{
    while (list != NULL)
    {
        for (uint8_t i = 0; i < list->count; i++)
            printf("%" PRIu64 " ", list->num);
        list = list->next;
    }
    printf("\n");
}
