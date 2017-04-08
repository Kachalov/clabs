#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef DEBUG
    #define DPRINT(...) printf("DEBUG: "); printf(__VA_ARGS__); printf("\n");
#else
    #define DPRINT(...)
#endif

typedef struct list
{
    uint32_t num;
    uint8_t count;
    struct list *next;
} list_t;

typedef struct
{
    uint8_t size;
    list_t *data;
} decomposed_t;

decomposed_t decompose(int num);

int main(void)
{
    unsigned int num;
    decomposed_t r;
    list_t *list = NULL;

    printf("Enter number: ");
    if (scanf("%d", &num) != 1)
    {
        printf("Input error\n");
        return 1;
    }

    r = decompose(num);
    for (uint8_t i = 0; i < r.size; i++)
    {
        if (list == NULL)
            list = r.data;
        else
            list = list->next;

        for (uint8_t j = 0; j < list->count; j++)
            printf("%d ", list->num);
    }
    printf("\n");

    return 0;
}

decomposed_t decompose(int num)
{
    decomposed_t r;
    list_t *list = NULL;

    r.size = 0;
    r.data = NULL;

    for (uint16_t i = 2; i <= num; i++)
    {
        if (num % i)
            continue;

        r.size++;

        list = malloc(sizeof(list_t));
        list->num = i;
        list->count = 0;

        if (r.data != NULL)
        {
            list->next = r.data;
        }
        r.data = list;

        DPRINT("List addr: %p->%p", r.data, list->next);

        while ((num % i == 0) && (num >= 2))
        {
            list->count++;
            num /= i;
        }
    }

    return r;
}
