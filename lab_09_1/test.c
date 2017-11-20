#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mystr.h"

int test_strcspn(const char *test, const char *str1, const char *str2);

int main(void)
{
    unsigned int err = 0;

    err += test_strcspn("empty1", "", "abc");
    err += test_strcspn("empty2", "abc", "");
    err += test_strcspn("end", "abc", "defjh");
    err += test_strcspn("begin", "123f", "2f13");
    err += test_strcspn("middle", "123f", "43a");

    printf("\nErrors: %u\n", err);
    return err != 0;
}

int test_strcspn(const char *test, const char *str1, const char *str2)
{
    size_t my_r = my_strcspn(str1, str2);
    size_t std_r = strcspn(str1, str2);

    if (std_r == my_r)
    {
        printf(".");
    }
    else
    {
        printf("E{name='%s', std=%zu, my=%zu}", test, std_r, my_r);
    }

    return my_r != std_r;
}
