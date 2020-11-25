
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

#define NEXT_TETROMINO_X 16
#define NEXT_TETROMINO_Y 4

#define INITIAL_POSITION_X 5
#define INITIAL_POSITION_Y -1

#define SPEED 100

#define N_TETROMINOS 6
#define TST  1
#define TET  2
#define TSW  3
#define TSWI 4
#define TSQ  5
#define TEL  6

#define TSTF  -1
#define TETF  -2
#define TSWF  -3
#define TSWIF -4
#define TSQF  -5
#define TELF  -6

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
	{3, 3, 0, 0}, \
	{0, 3, 3, 0}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
}

// skew tetromino
#define TSW1 {  \
	{0, 3, 0, 0}, \
	{3, 3, 0, 0}, \
	{3, 0, 0, 0}, \
	{0, 0, 0, 0}, \
}

// skew tetromino 2
#define TSWI0 {  \
	{0, 3, 3, 0}, \
	{3, 3, 0, 0}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
}

// skew tetromino 2
#define TSWI1 {  \
	{3, 0, 0, 0}, \
	{3, 3, 0, 0}, \
	{0, 3, 0, 0}, \
	{0, 0, 0, 0}, \
}

// square tetromino
#define TSQ0 {  \
	{4, 4, 0, 0}, \
	{4, 4, 0, 0}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
};

// L-tetromino
#define TEL0 {   \
	{5, 0, 0, 0}, \
	{5, 0, 0, 0}, \
	{5, 5, 0, 0}, \
	{0, 0, 0, 0}, \
};

#define TEL1 {   \
	{0, 0, 0, 0}, \
	{5, 5, 5, 0}, \
	{5, 0, 0, 0}, \
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

#define TYPE_GRID int grid[][LINES_WIDTH]

typedef struct {
	SDL_Color color;
	bool pinned;
	int type;
	int x, y;
	int variation;
	int piece[PIECE_VARIATIONS][PIECE_AREA_X][PIECE_AREA_Y];
} tetromino_t;

/**
 * GRID FUNCTIONS
 */
void init_grid(TYPE_GRID);
void print_grid(TYPE_GRID);
void clear_line(TYPE_GRID);
void draw_grid(SDL_Renderer* renderer, TYPE_GRID);

/**
 * TETROMINO FUNCTIONS
 */
tetromino_t* create_tetromino(int tetromino_type, int x, int y);
tetromino_t* create_from_next(tetromino_t* tetromino);
void draw_tetromino(SDL_Renderer* renderer, tetromino_t* tetromino);
void draw_next_tetromino(SDL_Renderer* renderer, tetromino_t* tetromino);
void update_tetromino(TYPE_GRID, tetromino_t** tetromino);
int get_random_piece();
bool can_move_right(TYPE_GRID, tetromino_t* tetromino);
bool can_move_left(TYPE_GRID, tetromino_t* tetromino);
bool can_rotate(TYPE_GRID, tetromino_t* tetromino);

/**
 * EVENTS FUNCTIONS
 */
void parse_input(SDL_Event* event, TYPE_GRID, tetromino_t* tetromino);


#endif // __TETRIS_H__
