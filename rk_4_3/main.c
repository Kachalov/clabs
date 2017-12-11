#include <stdio.h>

#include "student.h"
#include "list.h"

int main(void)
{
    int err = 0;
    list1_t *ss;

    setbuf(stdout, NULL);

    err = read_students(&ss);
    if (err)
        printf("Error: %d\n", err);
    else
    {
        for(list1_t *cur = ss; cur; cur = cur->next)
        {
            printf("%s %d\n",
                   ((student_t *)cur->data)->name,
                   ((student_t *)cur->data)->group);
        }
    }

    return 0;
}

