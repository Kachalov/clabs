#include <stdio.h>

#define ERR_NO_FILE -1
#define ERR_NOT_ENOUGH_ELEMENTS -2

int process(FILE *f, float *max1, float *max2);

int main(void)
{
    int status;
    float max1, max2;
    status = process(stdin, &max1, &max2);

    switch (status)
    {
        case 0:
        printf("%f %f\n", max1, max2);
        break;
    case ERR_NO_FILE:
        printf("No file found");
        break;
    case ERR_NOT_ENOUGH_ELEMENTS:
        printf("Not enough elements\n");
        break;
    default:
        printf("Unknown error: %d", status);
        break;
    }
    return status;
}

int process(FILE *f, float *max1, float *max2)
{
    float x;
    unsigned int i = 0;


    if (f == NULL)
    {
        return ERR_NO_FILE;
    }

    while (scanf("%f", &x))
    {
        if (*max1 <= x || i < 2)
        {
            *max2 = *max1;
            *max1 = x;
        }
        i++;
    }

    if (i < 2)
    {
        return ERR_NOT_ENOUGH_ELEMENTS;
    }

    return 0;
}
