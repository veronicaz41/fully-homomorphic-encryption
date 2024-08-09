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

#include "chickens.h"

// Unfortunately, having #pragma hls_top on more than one functions
// is not allowed right now.
// So I'm just moving this to the top of different function manually,
// and generate the circuits.
// We should probably fix the bazel scripts to allow having multiple
// #pragma hls_top per file, or we can split this into multiple folders
// which I'm too lazy to do now.

#pragma hls_top
struct Coords move_player(struct Coords coords, DIRECTION direction)
{
  struct Coords new_coords = coords;

  if (direction == MOVE_UP)
  {
    new_coords.x = (coords.x - 1 + BOARD_DIMS) % BOARD_DIMS;
  }
  else if (direction == MOVE_DOWN)
  {
    new_coords.x = (coords.x + 1) % BOARD_DIMS;
  }
  else if (direction == MOVE_LEFT)
  {
    new_coords.y = (coords.y - 1 + BOARD_DIMS) % BOARD_DIMS;
  }
  else if (direction == MOVE_RIGHT)
  {
    new_coords.y = (coords.y + 1) % BOARD_DIMS;
  }

  return new_coords;
}

struct Eggs lay_egg(struct Eggs eggs, struct Coords coords)
{
  struct Eggs new_eggs = {};

#pragma hls_unroll yes
  for (int i = 0; i < BOARD_DIMS; i++)
  {
#pragma hls_unroll yes
    for (int j = 0; j < BOARD_DIMS; j++)
    {
      new_eggs.has_egg[i][j] = (coords.x == i && coords.y == j) || eggs.has_egg[i][j];
    }
  }

  return new_eggs;
}

struct Eggs pickup_egg(struct Eggs eggs, struct Coords coords)
{
  struct Eggs new_eggs = {};

#pragma hls_unroll yes
  for (int i = 0; i < BOARD_DIMS; i++)
  {
#pragma hls_unroll yes
    for (int j = 0; j < BOARD_DIMS; j++)
    {
      if (coords.x == i && coords.y == j)
      {
        new_eggs.has_egg[i][j] = false;
      }
      else
      {
        new_eggs.has_egg[i][j] = eggs.has_egg[i][j];
      }
    }
  }

  return new_eggs;
}

struct Cell get_cell(struct Players players, struct Eggs eggs, struct Coords coords)
{
  struct Cell cell = {};

#pragma hls_unroll yes
  for (int i = 0; i < N_PLAYERS; i++)
  {
    cell.players[i] = (players.coords[i].x == coords.x) && (players.coords[i].y == coords.y);
  }

#pragma hls_unroll yes
  for (int i = 0; i < BOARD_DIMS; i++)
  {
#pragma hls_unroll yes
    for (int j = 0; j < BOARD_DIMS; j++)
    {
      if (coords.x == i && coords.y == j)
      {
        cell.egg = eggs.has_egg[i][j];
      }
    }
  }

  return cell;
}

// I need to split the update_egg function into pickup_egg and lay_egg
// Because for some reason, I get (Segmentation fault): process-wrapper failed: error executing command
// when I try to compile
// struct Eggs update_egg(struct Eggs eggs, struct Coords coords, bool has_egg)
// {
//   struct Eggs new_eggs = {};

// #pragma hls_unroll yes
//   for (int i = 0; i < BOARD_DIMS; i++)
//   {
// #pragma hls_unroll yes
//     for (int j = 0; j < BOARD_DIMS; j++)
//     {
//       if (coords.x == i && coords.y == j)
//       {
//         new_eggs.has_egg[i][j] = has_egg;
//       }
//       else
//       {
//         new_eggs.has_egg[i][j] = eggs.has_egg[i][j];
//       }
//     }
//   }

//   return new_eggs;
// }
