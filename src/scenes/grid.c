#include "grid.h"
#include "../log.h"
#include "../utils.h"


grid_t* grid_create(int rows, int cols, int pos_x, int pos_y) {
	LOG("Creating grid...");
	grid_t* new_grid = (grid_t*)malloc(sizeof(grid_t));

	ASSERT((new_grid == NULL), "Failed to create grid");

	new_grid->rows = rows;
	new_grid->cols = cols;
	new_grid->pos_x = pos_x;
	new_grid->pos_y = pos_y;

	int** data;
	data = malloc(rows * sizeof(*data));
	for (int i = 0; i < rows; i++) {
		data[i] = malloc(cols * sizeof(data[0]));
	}

	for (int i = 0;i < rows;i++) {
		for (int j = 0;j < cols;j++) {
			data[i][j] = 0;
		}
	}

	new_grid->data = data;

	LOG("Grid created");
	return new_grid;
}

void grid_print(grid_t* grid) {
	for (int i = 0;i < grid->rows;i++) {
		for (int j = 0;j < grid->cols;j++) {
			LOGF("%d\t", grid->data[i][j]);
		}
		LOG("\n");
	}
}
