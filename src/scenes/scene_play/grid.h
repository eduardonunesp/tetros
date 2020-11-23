
#ifndef GRID_H
#define GRID_H

#include "types.h"

#define COLS_NUMBER         10
#define ROWS_NUMBER         20
#define EXTRA_ROWS_NUMBER   22

typedef struct grid_s {
	int32_t rows, cols;
	int32_t x, y;
	int32_t cell_size;
	int32_t data[EXTRA_ROWS_NUMBER][COLS_NUMBER];
} grid_t;

grid_t*
grid_create(int32_t pos_x, int32_t pos_y, int32_t cell_size);

void
grid_print(const grid_t* grid);

bool
is_grid_full(const grid_t* grid);

uint32_t
grid_clear_line(grid_t* grid);

void
grid_clear(grid_t* grid);

#endif // GRID_H
