#include <stdio.h>

#define FLATS_PER_FLOOR 4
#define FLOORS_PER_ENTRANCE (9 * FLATS_PER_FLOOR)

int main(void)
{
    int flat;
    int entrance, floor;

    printf("Input flat number: ");
    scanf("%i", &flat);

    flat--;
    entrance = flat / FLOORS_PER_ENTRANCE + 1;
    floor = flat % FLOORS_PER_ENTRANCE / FLATS_PER_FLOOR + 1;

    printf("Entrance: %i, floor: %i\n", entrance, floor);
    return 0;
}
