#ifndef SCENE_END_H
#define SCENE_END_H

#include "types.h"

typedef struct game_s game_t;
typedef struct scene_s scene_t;

typedef struct scene_end_s {
	game_t* game;
} scene_end_t;

scene_t*
scene_end_create(game_t* game);

#endif // SCENE_END_H
