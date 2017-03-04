#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.1415926535897932384626433832795

int main(void)
{
    float a, b, h, alpha;
    float square;

    printf("Enter a, b, alpha: ");
    scanf("%f %f %f", &a, &b, &alpha);

    alpha = alpha/180.0*PI;
    h = fabs(a-b)/2.0*tan(alpha);

    // a == b or alpha > pi/2
    if(h <= 0)
    {
        printf("Invalid parameters\n");
        return 1;
    }

    square = (a+b)/2.0*h;
    printf("Square: %.3f\n", square);

    return 0;
}
