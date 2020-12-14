#ifndef __SCENE_PLAY_H__
#define __SCENE_PLAY_H__

#include "SDL2/SDL.h"

typedef struct game game_t;

typedef struct scene_play {} scene_play_t;

scene_play_t* scene_play_create();
void scene_play_init(game_t* game);
void scene_play_handle_events(game_t* game, SDL_Event* event);
void scene_play_loop(game_t* game);
void scene_play_destroy(game_t* game);


#endif // __SCENE_PLAY_H__
