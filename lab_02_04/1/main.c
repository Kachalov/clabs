#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#ifdef DEBUG
    #define DPRINT(...) {printf("DEBUG: "); printf(__VA_ARGS__); printf("\n");}
#else
    #define DPRINT(...)
#endif

typedef struct list
{
    uint64_t num;
    uint8_t count;
    struct list *next;
} list_t;

typedef struct
{
    uint8_t size;
    list_t *data;
} decomposed_t;

decomposed_t decompose(uint64_t num);
void print_list(decomposed_t r);

int main(void)
{
    uint64_t num;
    decomposed_t r;

    setbuf(stdout, NULL);

    printf("Enter number: ");
    if (scanf("%" SCNu64, &num) != 1)
    {
        printf("Input error\n");
        return 1;
    }

    r = decompose(num);
    print_list(r);

    return 0;
}

void print_list(decomposed_t r)
{
    list_t* list = NULL;

    for (uint8_t i = 0; i < r.size; i++)
    {
        if (list == NULL)
            list = r.data;
        else
            list = list->next;

        for (uint8_t j = 0; j < list->count; j++)
            printf("%" PRIu64 " ", list->num);
    }
    printf("\n");
}

decomposed_t decompose(uint64_t num)
{
    decomposed_t r;
    list_t *list = NULL;

    r.size = 0;
    r.data = NULL;

    for (uint64_t i = 2; i <= num; i++)
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

        DPRINT("List addr: %p->%p %" PRIu64, r.data, list->next, list->num);
	
	while ((num % i == 0) && (num >= 2))
        {
            list->count++;
            num /= i;
        }
    }

    return r;
}
