#include <stdio.h>
#include <math.h>

#define ERR_NO 0
#define ERR_NO_ELEMENTS 1
#define ERR_INPUT 2
#define ERR_SEEK 3
#define ERR_OPEN 4
#define ERR_NO_FILENAME 5
#define ERR_NO_FILE 6

float find_average(FILE *fd, unsigned char *err);
float find_closest(FILE *fd, float average, unsigned char *err);
void print_errcode(unsigned char err);

int main(int argc, char **argv)
{
    char *filename;
    FILE *fd;
    float average, closest;
    unsigned char err = 0;

    if (argc != 2)
    {
        print_errcode(ERR_NO_FILENAME);
        return 1;
    }
    filename = argv[1];
    
    fd = fopen(filename, "r");
    if (fd == NULL)
    {
        print_errcode(ERR_NO_FILE);
        return 1;
    }

    average = find_average(fd, &err);
    if (err)
        goto shutdown;

    if (fseek(fd, 0, SEEK_SET))
        goto shutdown;

    closest = find_closest(fd, average, &err);
    if (err)
        goto shutdown;

    printf("%f\n", closest);
    
    shutdown:
    if (err)
        print_errcode(err);
    fclose(fd);
    return err ? 1 : 0;
}

void print_errcode(unsigned char err)
{
    switch (err)
    {
        case ERR_NO:
            break;
        case ERR_NO_ELEMENTS:
            fprintf(stderr, "Error: No elements in file.\n");
            break;
        case ERR_INPUT:
            fprintf(stderr, "Error: Input error\n");
            break;
        case ERR_SEEK:
            fprintf(stderr, "Error: Could not seek file\n");
            break;
        case ERR_OPEN:
            fprintf(stderr, "Error: Could not open file\n");
            break;
        case ERR_NO_FILENAME:
            fprintf(stderr, "Error: Specify filename\n");
            break;
        case ERR_NO_FILE:
            fprintf(stderr, "Error: File not found\n");
            break;
        default:
            fprintf(stderr, "Unknown error: %d\n", err);
            break;
    }
}

float find_average(FILE *fd, unsigned char *err)
{
    float tmp;
    float avg = 0;
    unsigned int i = 0;

    *err = ERR_NO;

    while (fscanf(fd, "%f", &tmp) == 1)
    {
        avg += tmp;
        i++;
    }

    if (!i)
    {
        *err = ERR_INPUT;
        return 0;
    }

    return avg/i;
}

float find_closest(FILE *fd, float average, unsigned char *err)
{
    float tmp;
    float delta = 0;
    float delta_new = 0;
    float closest = 0;
    *err = ERR_NO;

    if (fscanf(fd, "%f", &tmp) != 1)
    {
        *err = ERR_INPUT;
        return 0;
    }

    delta = fabs(average - tmp);
    closest = tmp;

    while (fscanf(fd, "%f", &tmp) == 1)
    {
        delta_new = fabs(average - tmp);
        if (delta_new < delta)
        {
            delta = delta_new;
            closest = tmp;
        }
    }

    return closest;
}

