#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_BUF 100

int main(int argc, char **argv)
{
    FILE *f = NULL;
    char buf[MAX_BUF];
    char *cur = NULL;
    char *end = NULL;
    double x = 0;
    bool naned = false;

    if (argc > 1)
    {
        f = fopen(argv[1], "r");
        if (f != NULL)
        {
            while (fgets(buf, MAX_BUF, f))
            {
                cur = buf;
                do
                {
                    x = strtod(cur, &end);
                    if (cur == end)
                    {

                        while (!(('0' <= *cur && *cur <= '9')
                                 || *cur == '.'
                                 || *cur == '-'
                                 || *cur == '\0')
                               )
                        {
                            if (*cur == '\r'
                                    || *cur == '\n')
                            {
                                printf("\n");
                            }
                            else if (!(('0' <= *cur && *cur <= '9')
                                       || *cur == '.'
                                       || *cur == '-'))
                            {
                                if (!naned)
                                    printf("nan ");
                                naned = true;
                            }
                            cur++;
                        }
                        naned = false;
                    }
                    else
                    {
                        printf("%.2f ", x);
                        cur = end;
                    }
                }
                while (*cur != '\0');
            }
        }
        else
        {
            printf("File error\n");
        }
    }
    else
    {
        printf("No filename\n");
    }

    return 0;
}

