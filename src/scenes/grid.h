
#ifndef __GRID_H__
#define __GRID_H__

#include <SDL.h>

typedef struct grid {
	int rows, cols;
	int pos_x, pos_y;
	int cell_size;
	int** data;
} grid_t;

grid_t* grid_create(int rows, int cols, int pos_x, int pos_y, int cell_size);
void grid_print(grid_t* grid);
void clear_line(grid_t* grid);

#endif // __GRID_H__
