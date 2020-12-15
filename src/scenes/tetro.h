#ifndef __TETRO_H__
#define __TETRO_H__

#include <SDL.h>
#include <stdbool.h>

#define TETRO_TYPES 6
#define TETRO_VARIATIONS 4
#define TETRO_SQR_AREA 4
#define GRID_DEBUG_COLOR 255, 255, 255, 255

typedef struct grid grid_t;

typedef enum {
	TETRO_STRAIGHT,
	TETRO_TEE,
	TETRO_SKEW_LEFT,
	TETRO_SKEW_RIGHT,
	TETRO_SQUARE,
	TETRO_EL,
} tetro_type_e;

typedef enum {
	TETRO_MOVE_LEFT,
	TETRO_MOVE_RIGHT,
} tetro_move_e;

typedef enum {
	TETRO_ROTATE_CW,
	TETRO_ROTATE_CCW,
} tetro_rotate_e;

typedef struct tetro {
	tetro_type_e tetro_type;
	SDL_Color color;
	bool is_pinned;
	int grid_x, grid_y;
	int curr_variation;
	int data[TETRO_VARIATIONS][TETRO_SQR_AREA][TETRO_SQR_AREA];
} tetro_t;

tetro_t* tetro_create(tetro_type_e tetro_type);
void tetro_print(tetro_t* tetro);
void tetro_update_fall(tetro_t* tetro, grid_t* grid);
void tetro_rotate(tetro_t* tetro, tetro_rotate_e tetro_rotate, grid_t* grid);
void tetro_move_sideways(tetro_t* tetro, tetro_move_e tetro_move, grid_t* grid);

#endif // __TETRO_H__
