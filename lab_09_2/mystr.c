#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "errors.h"
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

char *my_str_replace(const char *source, const char *search, const char *replace)
{
    char *res = NULL;
    int num = -1;
    int num_rep = -1;
    int bytes_to_copy = 0;
    char *cur = NULL;
    const char *prev_src = source;

    for(const char *i = source; i != NULL;
        i = (i = strstr(i, search)) == NULL ? NULL : i + strlen(search), num++);
    cur = res = (char *)malloc(strlen(source) + 1 + num * (strlen(replace) - strlen(search)));

    for(const char *i = strstr(source, search); num_rep < num;
        i = i == NULL ? NULL : strstr(i, search), num_rep++)
    {
        DPRINT("cur{%s}", cur);
        DPRINT("prev_src{%s}", prev_src);
        DPRINT("i{%s}", i);
        if (i != NULL)
        {
            bytes_to_copy = i - prev_src;
            memcpy(cur, prev_src, bytes_to_copy);
            cur += bytes_to_copy;
            i += strlen(search);
            prev_src = i;
            strcpy(cur, replace);
            cur += strlen(replace);
        }
        else
        {
            strcpy(cur, prev_src);
        }
    }

    return res;
}
