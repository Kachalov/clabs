#include <stdio.h>

#define FLATS_PER_FLOOR 4
#define FLOORS_PER_ENTRANCE 9
#define FLATS_PER_ENTRANCE (FLATS_PER_FLOOR * FLOORS_PER_ENTRANCE)

int main(void)
{
    int flat;
    int entrance, floor;

    printf("Input flat number: ");
    scanf("%i", &flat);

    flat--;
    entrance = flat / FLATS_PER_ENTRANCE + 1;
    floor = flat % FLATS_PER_ENTRANCE / FLATS_PER_FLOOR + 1;

    printf("Entrance: %i, floor: %i\n", entrance, floor);
    return 0;
}
