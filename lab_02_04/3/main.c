#include <stdio.h>
#include <math.h>

float s(float x, float eps);
float f(float x);

int main(void)
{
    float x, eps;
    float s_result, f_result;
    float abs_err,  rel_err;

    printf("Enter x and eps: ");
    if (scanf("%f%f", &x, &eps) != 2)
    {
        printf("Error: invalid input\n");
        return 1;
    }

    if (fabs(x) >= 1)
    {
        printf("Error: |x| < 1\n");
        return 1;
    }

    s_result = s(x, eps);
    f_result = f(x);

    abs_err = fabs(s_result - f_result);
    rel_err = fabs(abs_err / f_result);
    
    printf("s(%.3f) = %.5e\n", x, s_result);
    printf("f(%.3f) = %.5e\n", x, f_result);
    printf("Abs error: %.5e\n", abs_err);
    printf("Relative error: %.5e\n", rel_err);

    return 0;
}

float s(float x, float eps)
{
    float r, ri, dr;
    int a, b;

    a = 1;
    b = 1;
    
    r = 1;
    ri = 1;

    do
    {
        dr = (2 * a++ - 1) * pow(x, 2)/(2 * b++);
        ri *= dr;
        r += ri;
    }
    while (fabs(ri) > eps);

    return r;
}

float f(float x)
{
    return 1/sqrt(1 - pow(x, 2));
}

