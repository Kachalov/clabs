#include <stdarg.h>
#include <stdbool.h>
#include <wchar.h>

#include "mystring.h"

#define SAFE_WRITE(b, n, s, c) do {\
if (0 <= b && b < n) *s++ = c;\
b++;\
} while (0)

int my_strcmp(const char *str1, const char *str2)
{
    const char *i = str1;
    const char *j = str2;
    for (; i && j; i++, j++)
        if (*i != *j)
            break;

    return *i - *j;
}

int my_snprintf(char *s, size_t n, const char *format, ...)
{
    va_list va;
    bool fmt = false;
    int bytes = 0;

    va_start(va, format);
    for (const char *i = format; *i; i++)
    {
        if (bytes < 0)
            break;

        if (fmt && *i != '%')
        {
            if (*i == 'c')
                SAFE_WRITE(bytes, n, s,  va_arg(va, int));

            fmt = false;
        }
        else if (*i == '%')
        {
            if (!fmt)
                fmt = true;
            else
            {
                SAFE_WRITE(bytes, n, s, '%');
                fmt = false;
            }
        }
        else if (!fmt)
        {
            SAFE_WRITE(bytes, n, s, *i);
        }
    }
    va_end(va);

    if (bytes >= n && n != 0)
        *(s - 1) = '\0';
    else
        *s = '\0';

    return bytes;
}
