#include <stdio.h>
#include "chickens.h"

// g++ -o chickens main.cc chickens.cc
// ./chicken
int main()
{
    struct Coords coords =
        {
            .x = 0,
            .y = 0};

    printf("Coords: (%d, %d)\n", coords.x, coords.y);

    coords = move_player(coords, MOVE_UP);
    printf("Move up, new coords: (%d, %d)\n", coords.x, coords.y);

    coords = move_player(coords, MOVE_DOWN);
    printf("Move down, new coords: (%d, %d)\n", coords.x, coords.y);

    coords = move_player(coords, MOVE_LEFT);
    printf("Move left, new coords: (%d, %d)\n", coords.x, coords.y);

    coords = move_player(coords, MOVE_RIGHT);
    printf("Move right, new coords: (%d, %d)\n", coords.x, coords.y);

    struct Eggs eggs = {};
    printf("Initialized with no eggs\n");

    struct Eggs new_eggs = lay_egg(eggs, coords);
    printf("Lay egg at: (%d, %d)\n", coords.x, coords.y);

    for (int i = 0; i < BOARD_DIMS; i++)
    {
        for (int j = 0; j < BOARD_DIMS; j++)
        {
            printf("%d ", new_eggs.has_egg[i][j]);
        }
        printf("\n");
    }

    struct Players players =
        {
            .coords = {coords, coords, coords, coords}};
    struct Cell cell = get_cell(players, new_eggs, coords);
    printf("Get cell at: (%d, %d) ;", coords.x, coords.y);
    for (int i = 0; i < N_PLAYERS; i++)
    {
        printf("player %d: %d ;", i, cell.players[i]);
    }
    printf("egg: %d\n", cell.egg);

    new_eggs = pickup_egg(eggs, coords);
    printf("Pick egg at: (%d, %d)\n", coords.x, coords.y);

    for (int i = 0; i < BOARD_DIMS; i++)
    {
        for (int j = 0; j < BOARD_DIMS; j++)
        {
            printf("%d ", new_eggs.has_egg[i][j]);
        }
        printf("\n");
    }

    return 0;
}
