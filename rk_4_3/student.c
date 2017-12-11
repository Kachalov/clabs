#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "student.h"
#include "list.h"

int student(student_t **s)
{
    int err = 0;

    *s = malloc(sizeof(student_t));
    if (*s)
    {
        strcpy((*s)->name, "");
        (*s)->group = 0;
        for (int i = 0; i < 5; i++)
            (*s)->marks[i] = 0;
    }
    else
    {
        err = 1;
    }

    return err;
}

void del_student(student_t **s)
{
    if (*s)
    {
        free(*s);
        *s = NULL;
    }
}

int read_students(list1_t **ss)
{
    int err = 0;
    student_t *s = NULL;
    FILE *fp = fopen("./in.txt", "r");


    if (!fp)
        err = 2;
    else
    {
        student(&s);
        while (!feof(fp))
        {
            int c = 0;

            err = student(&s);
            if ((c = fscanf(fp, "%s", s->name)) != 1)
            {
                //printf("%d\n", c);
                err = 3;
            }
            else if ((c = fscanf(fp, "%d", &s->group)) != 1)
            {
                //printf("%d\n", c);
                err = 4;
            }
            else
                for (int i = 0; i < 5; i++)
                    if (fscanf(fp, "%d", s->marks + i) != 1)
                        err = 5;

            fscanf(fp, "\n");

            if (err)
            {
                del_student(&s);
                break;
            }

            err = list_add(ss, s);

            if (err)
            {
                break;
            }

        }
    }

    return err;
}
