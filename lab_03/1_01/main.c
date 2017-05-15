#include <stdio.h>

#define ERR_NO 0
#define ERR_NO_FILE 1
#define ERR_NOT_ENOUGH_ELEMENTS 2

int process(FILE *f, float *max1, float *max2);

int main(void)
{
    int status;
    float max1, max2;
    status = process(stdin, &max1, &max2);

    switch (status)
    {
        case ERR_NO:
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
    float max_tmp;

    if (f == NULL)
    {
        return ERR_NO_FILE;
    }

    if (fscanf(f, "%f%f", max1, max2) != 2)
        return ERR_NOT_ENOUGH_ELEMENTS;

    if (*max1 < *max2)
    {
        max_tmp = *max1;
        *max1 = *max2;
        *max2 = max_tmp;
    }

    while (fscanf(f, "%f", &x) == 1)
    {
        if (*max1 <= x)
        {
            *max2 = *max1;
            *max1 = x;
        }
        else if (*max2 <=x)
        {
            *max2 = x;
        }
    }

    return ERR_NO;
}
