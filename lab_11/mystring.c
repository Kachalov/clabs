#include <stdarg.h>
#include <stdbool.h>
#include <wchar.h>

#include "mystring.h"

#define SAFE_WRITE(b, n, s, c) do {\
if (0 <= (b) && (b) < (n)) *(s)++ = (c);\
(b)++;\
} while (0)

int my_strcmp(const char *str1, const char *str2)
{
    const char *i = str1;
    const char *j = str2;
    for (; i && j && *i == *j; i++, j++);

    return *i - *j;
}

int my_snprintf(char *s, size_t n, const char *format, ...)
{
    va_list va;
    bool fmt = false;
    bool lmod = false;
    int bytes = 0;

    va_start(va, format);
    for (const char *i = format; *i && bytes >= 0; i++)
    {
        if (fmt && *i != '%')
        {
            switch (*i)
            {
                case 'c':
                    if (lmod)
                        SAFE_WRITE(bytes, n, s, va_arg(va, wchar_t));
                    else
                        SAFE_WRITE(bytes, n, s, va_arg(va, int));
                    fmt = false;
                    lmod = false;
                    break;
                case 's':
                    if (lmod)
                        for (wchar_t *i = va_arg(va, wchar_t *); *i; i++)
                            SAFE_WRITE(bytes, n, s, *i);
                    else
                        for (char *i = va_arg(va, char *); *i; i++)
                            SAFE_WRITE(bytes, n, s, *i);
                    fmt = false;
                    lmod = false;
                    break;
                case 'l':
                    lmod = true;
                    break;
            }
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
