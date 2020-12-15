#ifndef __SCENE_PLAY_H__
#define __SCENE_PLAY_H__

#include <SDL.h>
#include "grid.h"
#include "tetro.h"

#define GRID_ROWS 20
#define GRID_COLS 10
#define GRID_POSX 116
#define GRID_POSY 60
#define CELL_SIZE 24

typedef struct game game_t;

typedef struct play_events_t {
	int EVENT_TETRO_PINNED;
} play_events_t;

typedef struct scene_play {
	grid_t* grid;
	tetro_t* curr_tetro;
	unsigned int last_time;
	unsigned int current_time;
	play_events_t play_events;
} scene_play_t;

scene_play_t* scene_play_create();
void scene_play_init(game_t* game);
void scene_play_handle_events(game_t* game, SDL_Event* event);
void scene_play_handle_update(game_t* game);
void scene_play_rendering(game_t* game);
void scene_play_destroy(game_t* game);


#endif // __SCENE_PLAY_H__
