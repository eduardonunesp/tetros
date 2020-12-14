
#ifndef __GRID_H__
#define __GRID_H__

typedef struct grid {
	int rows, cols;
	int pos_x, pos_y;
	int** data;
} grid_t;

grid_t* grid_create(int rows, int cols, int pos_x, int pos_y);
void grid_print(grid_t* grid);

#endif // __GRID_H__
