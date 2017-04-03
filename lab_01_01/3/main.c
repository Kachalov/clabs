#include <stdio.h>

int main(void)
{
    float v0, v1, v2;
    float t0, t1, t2;

    printf("Input v1, t1, v2, t2 (m^3 and K): ");
    scanf("%f %f %f %f", &v1, &t1, &v2, &t2);

    if ((v1 < 0) || (v2 < 0))
    {
        printf("Invalid volumes\n");
        return 1;
    }

    if ((t1 < 0) || (t2 < 0))
    {
        printf("Invalid temperatures\n");
        return 1;
    }

    v0 = v1 + v2;
    t0 = (t1 * v1 + t2 * v2) / v0;

    printf("v0: %.3f m^3\nt0: %.3f K\n", v0, t0);
    return 0;
}
