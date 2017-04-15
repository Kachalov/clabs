#include <stdio.h>
#include <math.h>

float find_average(FILE *fd, unsigned char *err);
float find_closest(FILE *fd, float average, unsigned char *err);

int main(int argc, char **argv)
{
    char *filename;
    FILE *fd;
    float average, closest;
    unsigned char err = 0;

    if (argc != 2)
    {
        printf("Specify filename: %s file.txt\n", argv[0]);
        return 1;
    }
    filename = argv[1];
    
    fd = fopen(filename, "r");
    if (fd == NULL)
    {
        printf("File not found\n");
        return 2;
    }

    average = find_average(fd, &err);
    if (err)
    {
        // TODO: Add more inforamation about error.
        printf("Error: %d\n", err);
        goto close_fd;
    }
    fseek(fd, 0, SEEK_SET);
    closest = find_closest(fd, average, &err);
    printf("%f\n", closest);
    close_fd:
    fclose(fd);
}

float find_average(FILE *fd, unsigned char *err)
{
    float tmp;
    float avg = 0;
    int i = 0;

    while (fscanf(fd, "%f", &tmp) && !feof(fd))
    {
        avg += tmp;
        i++;
    }

    if (!i)
    {
        *err = 1;
        return 0;
    }

    return avg/i;
}

float find_closest(FILE *fd, float average, unsigned char *err)
{
    float tmp;
    float delta, delta_new;
    float closest;
    int i = 0;

    while (fscanf(fd, "%f", &tmp) && !feof(fd))
    {
        delta_new = fabs(average - tmp);
    if (delta_new < delta || !i++)
        {
            delta = delta_new;
            closest = tmp;
        }
    }

    if (!i)
    {
        *err = 1;
        return 0;
    }

    return closest;
}

