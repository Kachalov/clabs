#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mystring.h"

#define CREATE_BUF(b, n) char b##n[n] = "";

#define TEST_SNPRINTF(err, s, n, ...) do {\
    char tmp[n > 0 ? n : 1] = ""; int my, std;\
    my = my_snprintf(tmp, n, __VA_ARGS__);\
    std = snprintf(s, n, __VA_ARGS__);\
    if (strcmp(tmp, s) || std != my) {\
        fprintf(stderr, "E{my=(%d, %s), std=(%d, %s)}", my, tmp, std, s);\
        err++;\
    } else fprintf(stderr, ".");\
} while (0)


int main(void)
{
    unsigned int err = 0;
    CREATE_BUF(buf, 5);
    CREATE_BUF(buf, 10);
    CREATE_BUF(buf, 20);

    TEST_SNPRINTF(err, buf5, 0, " ");
    TEST_SNPRINTF(err, buf5, 5, "%c--%%c--%c", 'a', 'f');
    TEST_SNPRINTF(err, buf10, 10, "%c--%%c--%c", 'a', 'f');
    TEST_SNPRINTF(err, buf20, 20, "%s/%c", "%abe", '!');

    printf("\nErrors: %u\n", err);
    return err != 0;
}

