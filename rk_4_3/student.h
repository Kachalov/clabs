#pragma once

#include "list.h"

typedef struct
{
    char name[80];
    int group;
    int marks[5];
} student_t;

int student(student_t **s);
void del_student(student_t **s);
int read_students(list1_t **ss);
