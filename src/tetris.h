
#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "log.h"

#define GAME_TITLE "Tetris"
#define GAME_TITLE_DEAD "Tetris (DEAD)"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640

#define LINES_WIDTH 10
#define LINES_HEIGHT 20

#define GRID_X_OFFSET 116
#define GRID_Y_OFFSET 60

#define PIECE_AREA_X 4
#define PIECE_AREA_Y 4
#define PIECE_VARIATIONS 4
#define CELL_SIZE 24

#define SPEED 100

#define TST 1
#define TET 2
#define TSW 3
#define TSQ 4
#define TEL 5

#define TSTF -1
#define TETF -2
#define TSWF -3
#define TSQF -4
#define TELF -5

// straight tetromino
#define TST0 {  \
	{1,0,0,0}, \
	{1,0,0,0}, \
	{1,0,0,0}, \
	{1,0,0,0}, \
}

#define TST1 {  \
	{0,0,0,0}, \
	{1,1,1,1}, \
	{0,0,0,0}, \
	{0,0,0,0}, \
}

// T-tetromino
#define TET0 {  \
	{0, 2, 0, 0}, \
	{2, 2, 2, 0}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
}

#define TET1 {  \
	{0, 2, 0, 0}, \
	{0, 2, 2, 0}, \
	{0, 2, 0, 0}, \
	{0, 0, 0, 0}, \
}

#define TET2 {  \
	{0, 0, 0, 0}, \
	{2, 2, 2, 0}, \
	{0, 2, 0, 0}, \
	{0, 0, 0, 0}, \
}

#define TET3 {  \
	{0, 2, 0, 0}, \
	{2, 2, 0, 0}, \
	{0, 2, 0, 0}, \
	{0, 0, 0, 0}, \
}

// skew tetromino
#define TSW0 {  \
	{0, 3, 3, 0}, \
	{0, 0, 3, 3}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
}

// skew tetromino
#define TSW1 {  \
	{0, 0, 3, 0}, \
	{0, 3, 3, 0}, \
	{0, 3, 0, 0}, \
	{0, 0, 0, 0}, \
}

// square tetromino
#define TSQ0 {  \
	{0, 4, 4, 0}, \
	{0, 4, 4, 0}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
};

// L-tetromino
#define TEL0 {   \
	{0, 5, 0, 0}, \
	{0, 5, 0, 0}, \
	{0, 5, 5, 0}, \
	{0, 0, 0, 0}, \
};

#define TEL1 {   \
	{0, 0, 0, 0}, \
	{0, 5, 5, 5}, \
	{0, 5, 0, 0}, \
	{0, 0, 0, 0}, \
};

#define TEL2 {   \
	{5, 5, 0, 0}, \
	{0, 5, 0, 0}, \
	{0, 5, 0, 0}, \
	{0, 0, 0, 0}, \
};

#define TEL3 {   \
	{0, 0, 5, 0}, \
	{5, 5, 5, 0}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
};

int accelerate;
int grid[LINES_HEIGHT][LINES_WIDTH];

typedef struct {
	SDL_Color color;
	bool pinned;
	int type;
	int x, y;
	int variation;
	int piece[PIECE_VARIATIONS][PIECE_AREA_X][PIECE_AREA_Y];
} tetromino_t;

tetromino_t* curr_tetromino;

/**
 * GRID FUNCTIONS
 */
void init_grid();
void print_grid();
void clear_line();
void draw_grid(SDL_Renderer* renderer);

/**
 * TETROMINO FUNCTIONS
 */
tetromino_t* create_tetromino(int tetromino_type);
void draw_tetromino(SDL_Renderer* renderer);
void update_tetromino();
int get_random_piece();
bool can_move_right();
bool can_move_left();
bool can_rotate();

/**
 * EVENTS FUNCTIONS
 */
void parse_input(SDL_Event* event);


#endif // __TETRIS_H__
