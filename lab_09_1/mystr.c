#include "mystr.h"

size_t my_strcspn(const char *str1, const char *str2)
{
    const char *i = str1;
    for (; *i != '\0'; i++)
        for (const char *j = str2; *j != '\0'; j++)
        {
            if (*i == *j)
                return i - str1;
        }

    return i - str1;
}