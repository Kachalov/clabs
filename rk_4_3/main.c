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
        int group_name[5];
        int group_data[5];
        int group = 0;
        int max = 0;

        printf("Source: \n");
        for(list1_t *cur = ss; cur && cur->data; cur = cur->next)
        {
            printf("%s %d\n",
                   ((student_t *)cur->data)->name,
                   ((student_t *)cur->data)->group);

            int found = 0;
            for (int i = 0; i < group; i++)
            {
                if (group_name[i] == ((student_t *)cur->data)->group)
                {
                    found = 1;
                    for (int j = 0 ; j < 5; j++)
                    {
                        if (((student_t *)cur->data)->marks[j] < 3)
                            group_data[i]++;
                    }

                    if (group_data[i] > max)
                        max = group_data[i];
                }
            }

            if (!found)
            {
                group_data[group] = 0;
                group_name[group] = ((student_t *)cur->data)->group;
                group++;
            }
        }

        for(list1_t *cur = ss; cur && cur->data; cur = cur->next)
        {
            int found = 0;
            for (int i = 0; i < group; i++)
                if (group_name[i] == ((student_t *)cur->data)->group)
                {
                    del_student((student_t **)&cur->data);
                    list_del(&cur);
                    found = 1;
                }

            if (!found)
            {
                cur = cur->next;
            }
        }

        printf("Result: \n");
        for(list1_t *cur = ss; cur && cur->data; cur = cur->next)
        {
            printf("%s %d\n",
                   ((student_t *)cur->data)->name,
                   ((student_t *)cur->data)->group);
        }
    }

    return 0;
}

