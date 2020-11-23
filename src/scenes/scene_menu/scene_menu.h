#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include "types.h"

typedef struct game_s game_t;
typedef struct scene_s scene_t;

typedef struct scene_menu_s {
	game_t* game;
} scene_menu_t;

scene_t*
scene_menu_create(game_t* game);

#endif // SCENE_MENU_H
