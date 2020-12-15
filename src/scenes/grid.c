#include "grid.h"
#include "../log.h"
#include "../utils.h"


grid_t* grid_create(int rows, int cols, int pos_x, int pos_y, int cell_size) {
	LOG("Creating grid...");
	grid_t* new_grid = (grid_t*)malloc(sizeof(grid_t));

	ASSERT((new_grid == NULL), "Failed to create grid");

	new_grid->rows = rows;
	new_grid->cols = cols;
	new_grid->pos_x = pos_x;
	new_grid->pos_y = pos_y;
	new_grid->cell_size = cell_size;

	int** data;
	data = malloc(rows * sizeof(*data));
	for (int i = 0; i < rows; i++) {
		data[i] = malloc(cols * sizeof(data[0]));
	}

	for (int y = 0;y < rows;y++) {
		for (int x = 0;x < cols;x++) {
			data[y][x] = 0;
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

void clear_line(grid_t* grid) {
	int lines_to_clear[] = { 0,0,0,0 };
	int lines_count = 0;

	for (int y = grid->rows - 1; y > 0; y--) {
		int count = 0;
		for (int x = 0; x < grid->cols; x++) {
			if (grid->data[y][x] != 0) {
				if (++count == grid->cols) {
					// Found non zero line
					lines_to_clear[lines_count] = y;
					lines_count++;
					LOGF("Found lines %d\n", y);
				}
			}
		}
	}

	if (lines_count > 0) {
		int curr_line = lines_to_clear[0];
		for (int y = grid->rows - 1; y > 0; y--) {
			for (int x = 0; x < grid->cols; x++) {
				int next_y = y + (curr_line == y ? 1 : 0) + 1;
				if (next_y <= grid->rows) {
					grid->data[next_y][x] = grid->data[y][x];
				}
			}
		}
	}
}
