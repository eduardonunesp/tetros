#ifndef SCENE_PLAY_H
#define SCENE_PLAY_H

#include "types.h"
#include "grid.h"
#include "tetro.h"
#include "gui/gui.h"

#define GRID_ROWS 20
#define GRID_COLS 10
#define GRID_POSX 10
#define GRID_POSY 10
#define CELL_SIZE 22
#define DRAW_SIZE 24

#define NEXT_POSX 160
#define NEXT_POSY 20

#define DPAD_POS   40, 560
#define BTN_RL_POS 200, 560
#define BTN_RR_POS 240, 560

typedef struct game_s game_t;
typedef struct scene_s scene_t;

typedef struct play_events_s {
	int32_t EVENT_TETRO_PINNED;
} play_events_s;

typedef enum {
	SCENE_STATE_WAITING,
	SCENE_STATE_READY,
	SCENE_STATE_PLAYING,
	SCENE_STATE_PAUSE,
	SCENE_STATE_RESUME,
	SCENE_STATE_GAMEOVER,
} scene_state_e;

typedef struct scene_play_s {
	grid_t*  grid;
	tetro_t* curr_tetro;
	tetro_t* next_tetro;

	dpad_t*   dpad;
	button_t* rotate_l;
	button_t* rotate_r;

	int32_t stats[TETRO_TYPES];

	play_events_s play_events;

	scene_state_e state;
	game_t* game;

	uint32_t score;
	uint32_t level;
	uint32_t next_level;
} scene_play_t;

scene_t*
scene_play_create(game_t* game);

#endif // SCENE_PLAY_H
