#ifndef TETRO_H
#define TETRO_H

#include "types.h"

#define TETRO_TYPES      8
#define TETRO_VARIATIONS 4
#define TETRO_SQR_AREA   4
#define GRID_DEBUG_COLOR 255, 255, 255, 255

static SDL_Color TETRO_COLORS[TETRO_TYPES] = {
	{   0,   0,   0, 255 }, // NONE
	{   0, 240, 240, 255 }, // TETRO_I
	{ 160,   0, 240, 255 }, // TETRO_T
	{   0, 240,   0, 255 }, // TETRO_S
	{ 240,   0,   0, 255 }, // TETRO_Z
	{ 240, 240,   0, 255 }, // TETRO_O
	{ 240, 160,   0, 255 }, // TETRO_L
	{   0,   0, 240, 255 }, // TETRO_J
};

typedef struct scene_play_s scene_play_t;
typedef struct grid_s grid_t;

typedef enum {
	TETRO_NONE,
	TETRO_I,
	TETRO_T,
	TETRO_S,
	TETRO_Z,
	TETRO_O,
	TETRO_L,
	TETRO_J,
} tetro_type_e;

typedef enum {
	TETRO_MOVE_LEFT,
	TETRO_MOVE_RIGHT,
} tetro_move_e;

typedef enum {
	TETRO_ROTATE_CW,
	TETRO_ROTATE_CCW,
} tetro_rotate_e;

typedef struct tetro_s {
	SDL_Color    color;
	tetro_type_e tetro_type;
	
	int32_t  grid_x, grid_y;
	int32_t  curr_rotate;
	bool is_pinned;

	int32_t data[TETRO_VARIATIONS][TETRO_SQR_AREA][TETRO_SQR_AREA];
} tetro_t;

tetro_t*
tetro_create(tetro_type_e t_type);

void
tetro_reset(tetro_t* t);

void
tetro_print(tetro_t* t);

void
tetro_update_fall(tetro_t* t, grid_t* grid, scene_play_t* scn_play);

void
tetro_rotate(tetro_t* t, tetro_rotate_e t_rotate, grid_t* grid);

void
tetro_move_sideways(tetro_t* t, tetro_move_e t_move, grid_t* grid);

tetro_type_e
tetro_take_piece();

#endif // TETRO_H
