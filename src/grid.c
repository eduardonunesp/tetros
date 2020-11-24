#include "tetris.h"
#include "log.h"
#include <SDL2/SDL.h>

void init_grid() {
	int counter = 0;
	for (int y = 0; y < LINES_HEIGHT; y++) {
		for (int x = 0; x < LINES_WIDTH; x++) {
			grid[y][x] = 0;
			counter++;
		}
	}

	// for (int x = 0; x < LINES_WIDTH; x++) {
	// 	grid[19][x] = -1;
	// 	grid[18][x] = -1;
	// 	grid[17][x] = -1;
	// }

	// grid[19][0] = 0;
	// grid[18][0] = 0;
	// grid[17][0] = 0;

	LOGF("Grid created with %d positions\n", counter);
}

void print_grid() {
	int counter = 1;
	for (int y = 0; y < LINES_HEIGHT; y++) {
		for (int x = 0; x < LINES_WIDTH; x++) {
			LOGF("\t%d", grid[y][x]);
			if (counter % 10 == 0) {
				LOG("\n");
			}
			counter++;
		}
	}
}

void clear_line() {
	int lines_to_clear[4] = { 0, 0, 0, 0 };
	int lines_count = 0;
	bool should_clear = false;

	for (int y = 0; y < LINES_HEIGHT; y++) {
		bool has_line = true;

		for (int x = 0; x < LINES_WIDTH; x++) {
			if (grid[y][x] == 0) {
				has_line = false;
			}
		}

		if (has_line) {
			lines_to_clear[lines_count] = y;
			lines_count++;
		}
	}

	for (int line_index = 0; line_index < lines_count; line_index++) {
		if (lines_to_clear[line_index]) {
			LOGF("Has line %d\n", line_index);
			should_clear = true;

			for (int x = 0; x < LINES_WIDTH; x++) {
				grid[lines_to_clear[line_index]][x] = 0;
			}
		}
	}

	if (should_clear) {
		int last_index = lines_to_clear[lines_count - 1];
		LOGF("Last index %d\n", last_index);
		for (int y = last_index - 1; y > 0; y--) {
			for (int x = 0; x < LINES_WIDTH; x++) {
				LOGF("%d %d\n", y, x);
				grid[y + lines_count][x] = grid[y][x];
			}
		}
	}
}

void draw_grid(SDL_Renderer* renderer) {
	for (int y = 0; y <= LINES_HEIGHT; y++) {
		for (int x = 0; x <= LINES_WIDTH; x++) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(renderer,
				GRID_X_OFFSET + (x * CELL_SIZE),
				GRID_Y_OFFSET,
				GRID_X_OFFSET + (x * CELL_SIZE),
				GRID_Y_OFFSET + (LINES_HEIGHT * CELL_SIZE)
			);

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(renderer,
				GRID_X_OFFSET,
				GRID_Y_OFFSET + (y * CELL_SIZE),
				GRID_X_OFFSET + (LINES_WIDTH * CELL_SIZE),
				GRID_Y_OFFSET + (y * CELL_SIZE)
			);
		}
	}

	for (int y = 0; y < LINES_HEIGHT; y++) {
		for (int x = 0; x < LINES_WIDTH; x++) {
			int piece = grid[y][x];

			// Negative numbers for pieces fixed
			if (piece < 0) {
				SDL_Color color;

				switch (piece)
				{
				case -1:
					color.r = 0;
					color.g = 255;
					color.b = 255;
					break;
				case -2:

					color.r = 255;
					color.g = 0;
					color.b = 255;
					break;
				case -3:

					color.r = 255;
					color.g = 0;
					color.b = 0;
					break;
				case -4:

					color.r = 255;
					color.g = 255;
					color.b = 0;
					break;
				case -5:
					color.r = 0;
					color.g = 0;
					color.b = 255;
					break;
				default:
					break;
				}

				SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);

				SDL_Rect rect = {
					GRID_X_OFFSET + (x * CELL_SIZE), GRID_Y_OFFSET + (y * CELL_SIZE),
					CELL_SIZE, CELL_SIZE,
				};

				SDL_RenderFillRect(renderer, &rect);
				SDL_RenderDrawRect(renderer, &rect);
			}
		}
	}
}

