#include "tetris.h"
#include "log.h"
#include <SDL2/SDL.h>

void init_grid(TYPE_GRID) {
	int counter = 0;

	int grid_ref[LINES_HEIGHT][LINES_WIDTH] = {
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
	};

	for (int y = 0; y < LINES_HEIGHT; y++) {
		for (int x = 0; x < LINES_WIDTH; x++) {
			grid[y][x] = grid_ref[y][x];
			counter++;
		}
	}

	LOGF("Grid created with %d positions\n", counter);
}

void print_grid(TYPE_GRID) {
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

void clear_line(TYPE_GRID) {
	int lines_to_clear[] = { 0,0,0,0 };
	int lines_count = 0;

	for (int y = LINES_HEIGHT - 1; y > 0; y--) {
		int count = 0;
		for (int x = 0; x < LINES_WIDTH; x++) {
			if (grid[y][x] != 0) {
				if (++count == LINES_WIDTH) {
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
		for (int y = LINES_HEIGHT - 1; y > 0; y--) {
			for (int x = 0; x < LINES_WIDTH; x++) {
				int next_y = y + (curr_line == y ? 1 : 0) + 1;
				if (next_y <= LINES_HEIGHT) {
					grid[next_y][x] = grid[y][x];
				}
			}
		}
	}
}

void draw_grid(SDL_Renderer* renderer, TYPE_GRID) {
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
				case TSTF:
					color.r = 0;
					color.g = 255;
					color.b = 255;
					break;
				case TETF:
					color.r = 255;
					color.g = 0;
					color.b = 255;
					break;
				case TSWF:
				case TSWIF:
					color.r = 255;
					color.g = 0;
					color.b = 0;
					break;
				case TSQF:
					color.r = 255;
					color.g = 255;
					color.b = 0;
					break;
				case TELF:
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

