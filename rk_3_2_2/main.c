#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
            int j = 0;
            while (fgets(buf, MAX_BUF, f))
            {
                j++;
                int i = 0;
                cur = buf;
                //printf("While '%s' %d:\n", buf, j);
                do
                {
                    i++;
                    x = strtod(cur, &end);
                    //printf("S '%s'\n", cur);
                    if (cur == end
                            || ( !(
                               *end == '\r'
                               || *end == '\n'
                               || *end == ' ')))
                    {
                        //printf("true %p %p (%c)\n", cur, end, *cur);
                        while ('0' <= *cur && *cur <= '9')
                        {
                            if (!naned)
                                printf("nan ");
                            naned = true;
                            cur++;
                        }
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
                            //printf("i");
                            cur++;
                        }
                        naned = false;
                        //printf("\n");
                    }
                    else
                    {
                        printf("%.2f ", x);
                        cur = end;
                    }
                    //printf("%p %p\n", cur, buf + MAX_BUF - 1);
                }
                while (cur != buf + MAX_BUF && i < 10);
                strcpy(buf, "");
            }
        }
        else
        {
            printf("File error\n");
        }
    }
    else
    {
        printf("No filename");
    }

    return 0;
}

