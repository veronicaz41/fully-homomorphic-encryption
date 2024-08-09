// Copyright 2021 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FULLY_HOMOMORPHIC_ENCRYPTION_TRANSPILER_EXAMPLES_CHICKENS_CHICKENS_H_
#define FULLY_HOMOMORPHIC_ENCRYPTION_TRANSPILER_EXAMPLES_CHICKENS_CHICKENS_H_

#define BOARD_DIMS 4 // board would be BOARD_DIMS * BOARD_DIMS
#define N_PLAYERS 4

enum DIRECTION
{
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT
};

struct Coords
{
    unsigned char x;
    unsigned char y;
};

struct Players
{
    struct Coords coords[N_PLAYERS];
};

struct Eggs
{
    bool has_egg[BOARD_DIMS][BOARD_DIMS];
};

struct Cell
{
    bool players[N_PLAYERS]; // if the player is at this cell
    bool egg;
};

struct Coords move_player(struct Coords coords, DIRECTION direction);

struct Eggs lay_egg(struct Eggs eggs, struct Coords coords);

struct Eggs pickup_egg(struct Eggs eggs, struct Coords coords);

// struct Eggs update_egg(struct Eggs eggs, struct Coords coords, bool has_egg);

struct Cell get_cell(struct Players players, struct Eggs eggs, struct Coords coords);

#endif // FULLY_HOMOMORPHIC_ENCRYPTION_TRANSPILER_EXAMPLES_CHICKENS_CHICKENS_I_H_
