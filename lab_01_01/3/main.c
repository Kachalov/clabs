#include <stdio.h>

int main(void)
{
    float v0, v1, v2;
    float t0, t1, t2;

    printf("Input v1, t1, v2, t2: ");
    scanf("%f %f %f %f", &v1, &t1, &v2, &t2);

    if((v1 < 0) | (v2 < 0))
    {
        printf("Invalid V\n");
        return 1;
    }

    v0 = v1 + v2;
    t0 = (t1*v1 + t2*v2)/v0;

    printf("v0: %.3f; t0: %.3f\n", v0, t0);
    return 0;
}
