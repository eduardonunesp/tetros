#include "grid.h"
#include "log.h"
#include "utils.h"

grid_t*
grid_create(int32_t pos_x, int32_t pos_y, int32_t cell_size) {
	LOG("Creating grid...");
	grid_t* new_grid = NEW(grid_t);

	ASSERT((new_grid == NULL), "Failed to create grid");

	new_grid->rows      = ROWS_NUMBER;
	new_grid->cols      = COLS_NUMBER;
	new_grid->x         = pos_x;
	new_grid->y         = pos_y;
	new_grid->cell_size = cell_size;

#ifdef _DEBUG
	int32_t grid_ref[EXTRA_ROWS_NUMBER][COLS_NUMBER] = {
		#include "debug_grid.txt"
	};
#endif

	for (int32_t y = 0;y < EXTRA_ROWS_NUMBER;y++)
		for (int32_t x = 0;x < new_grid->cols;x++)
#ifdef _DEBUG
			new_grid->data[y][x] = grid_ref[y][x];
#else
			new_grid->data[y][x] = 0;
#endif

	LOG("Grid created");
	return new_grid;
}

void
grid_print(const grid_t* grid) {
#ifdef _DEBUG
	for (int32_t y = 0;y < grid->rows;y++) {
		LOGF("(%d)\t", y);
		for (int32_t x = 0;x < grid->cols;x++)
			LOGF("%d\t", grid->data[y][x]);
		LOG("\n");
	}
#endif
}

bool
is_grid_full(const grid_t* grid)
{
	for (int32_t y = EXTRA_ROWS_NUMBER - grid->rows; y > 0; y--)
		for (int32_t x = 0;x < grid->cols;x++)
			if (grid->data[y][x] != 0)
				return true;
	return false;
}

void
mark_to_clear_line(int32_t grid[][COLS_NUMBER], int32_t line) {
	for (int32_t x = 0; x < COLS_NUMBER; x++)
		grid[line][x] = 0;
}

uint32_t
grid_clear_line(grid_t* grid) {
	int32_t lines[ROWS_NUMBER] = { 0 };
	int32_t start = -1;
	uint32_t lines_count = 0;
	memset(&lines, 0, sizeof(int32_t[ROWS_NUMBER]));

	for (int32_t y = grid->rows - 1; y > 0; y--) {
		int32_t count = 0;
		for (int32_t x = 0; x < grid->cols; x++) {
			if (grid->data[y][x] < 0) {
				if (++count == grid->cols) {
					// Found non zero line
					if (start == -1) {
						start = y;
						LOGF("Start %d\n", start);
					}
					lines[y] = 1;
					lines_count++;
					LOGF("Found lines %d\n", y);
				}
			}
		}
	}

	for (int32_t y = start - 1; y > 0; y--)
		for (int32_t x = 0; x < grid->cols; x++)
			grid->data[y + 1][x] = grid->data[y][x];

	return lines_count;
}

void
grid_clear(grid_t* grid)
{
	for (int32_t y = 0;y < EXTRA_ROWS_NUMBER;y++)
		for (int32_t x = 0;x < grid->cols;x++)
			grid->data[y][x] = 0;
}
