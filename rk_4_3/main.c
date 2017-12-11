#include <stdio.h>

#include "student.h"
#include "list.h"

int main(void)
{
    int err = 0;
    list1_t *ss = NULL;

    setbuf(stdout, NULL);

    err = read_students(&ss);
    if (err)
        printf("Error: %d\n", err);
    else
    {
        int group_name[100];
        int group_data[100];
        int group = 0;
        int max = 0;

        printf("Source: \n");
        for(list1_t *cur = ss; cur; cur = cur->next)
        {
            printf("%s %d\n",
                   ((student_t *)cur->data)->name,
                   ((student_t *)cur->data)->group);

            int found = -1;
            for (int i = 0; i < group; i++)
            {
                if (group_name[i] == ((student_t *)cur->data)->group)
                {
                    found = i;
                    break;
                }
            }

            if (found == -1)
            {
                group_data[group] = 0;
                group_name[group] = ((student_t *)cur->data)->group;
                found = group++;
            }

            for (int j = 0 ; j < 5; j++)
            {
                if (((student_t *)cur->data)->marks[j] < 3)
                    group_data[found]++;
            }

            if (group_data[found] > max)
                max = group_data[found];
        }

        list1_t *prev = NULL;
        for(list1_t *cur = ss; cur;)
        {
            int found = 0;
            for (int i = 0; i < group; i++)
                if (group_name[i] == ((student_t *)cur->data)->group &&
                    group_data[i] == max)
                {
                    del_student((student_t **)&cur->data);
                    list_del(&cur);
                    if (prev)
                        prev->next = cur;
                    else
                        ss = cur;
                    found = 1;
                }

            prev = cur;
            if (!found)
            {
                cur = cur->next;
            }
        }

        printf("\nResult: \n");
        for(list1_t *cur = ss; cur; cur = cur->next)
        {
            printf("%s %d\n",
                   ((student_t *)cur->data)->name,
                   ((student_t *)cur->data)->group);
        }
    }

    return 0;
}
