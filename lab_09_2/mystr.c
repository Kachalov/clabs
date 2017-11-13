#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "mystr.h"

#define REALLOC_ADD BUFSIZ

ssize_t realloc_size(int x)
{
    return x * REALLOC_ADD;
}

ssize_t my_getline(char **lp, size_t *n, FILE *fd)
{
    *lp = NULL;
    char *tmp = NULL;
    char buf[REALLOC_ADD] = "";
    *n = 0;
    int i = 0;
    size_t len = REALLOC_ADD - 1;

    if (feof(fd))
        *n = EOF;

    while (!feof(fd) && len == REALLOC_ADD - 1)
    {
        fgets(buf, REALLOC_ADD, fd);
        if ((tmp = (char *) realloc(*lp, realloc_size(++i))) != NULL)
        {
            *lp = tmp;
            len = strcspn(buf, "\r\n");
            if (len == 0)
            {
                memcpy(*lp + *n, "\0", 1);
            }
            else
            {
                memcpy(*lp + *n, buf, len);
                memcpy(*lp + *n + len, "\0", 1);
                *n += len;
            }
        }
        else
        {
            *n = EOF;
            free(*lp);
            break;
        }
    }

    return *n;
}

char *str_replace(const char *source, const char *search, const char *replace)
{
    char *res = (char *)malloc(strlen(source) + 1);
    strcpy(res, source);
    return res;
}
