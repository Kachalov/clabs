#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mystring.h"

#define TEST_SNPRINTF(s, ...) do {\
printf("my:       %d ", my_snprintf(s, __VA_ARGS__));\
printf("%s\n", s);\
printf("original: %d ", snprintf(s, __VA_ARGS__));\
printf("%s\n", s);\
} while (0)

#define CREATE_BUF(b, n) char b##n[n];

int main(void)
{
    unsigned int err = 0;
    CREATE_BUF(buf, 10);
    CREATE_BUF(buf, 5);

    TEST_SNPRINTF(buf10, 10, "%c--%%c--%c", 'a', 'c');
    TEST_SNPRINTF(buf5, 5, "%c--%%c--%c", 'a', 'c');

    printf("\nErrors: %u\n", err);
    return err != 0;
}

