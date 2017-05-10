#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define EPS 1e-7

typedef struct
{
    float x;
    float y;
} point2d_t;

bool contains(point2d_t begin, point2d_t end, point2d_t point);
float segment_length(point2d_t begin, point2d_t end);

int main(void)
{
    point2d_t a, b;
    point2d_t x;
    
    printf("Enter a(x, y) and b(x, y): ");
    if (scanf("%f%f%f%f", &(a.x), &(a.y), &(b.x), &(b.y)) != 4)
    {
        printf("Incorrect input\n");
        return 1;
    }

    printf("Enter X(x, y): ");                
    if (scanf("%f%f", &(x.x), &(x.y)) != 2)
    {
        printf("Incorrect input\n");
        return 1;
    }

    if (contains(a, b, x))
    {
        printf("Contains\n");
    }
    else
    {
        printf("Does not contain\n");
    }

    
    return 0;
}

bool contains(point2d_t begin, point2d_t end, point2d_t point)
{
    float len_ab, len_ax, len_bx;
    len_ab = segment_length(begin, end);
    len_ax = segment_length(begin, point);
    len_bx = segment_length(end, point);

    return fabs(-len_ab + len_ax + len_bx) <= EPS;
}

float segment_length(point2d_t begin, point2d_t end)
{
    return sqrt(pow(begin.x - end.x, 2) + pow(begin.y - end.y, 2));
}

