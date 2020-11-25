#include "tetris.h"
#include "log.h"
#include <SDL2/SDL.h>

void init_grid() {
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
		// {0,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
		// {0,-1,-1,-1,-1,-1,-1,0,-1,-1,},
		// {0,-1,-1,-1,-1,-1,-1,0,-1,-1,},
		// {0,-1,-1,-1,-1, 0,-2,-1,-1,-1,},
		// {0,-1,-1,-1,-1,-2,-2,-2,-1,-1,},
		// {0,-1,-1,-1,-1,-4,-4,0,-1,-1,},
		// {0,-1,-1,-1,-1,-4,-4,0,-1,-1,},
		// {0,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
	};

	for (int y = 0; y < LINES_HEIGHT; y++) {
		for (int x = 0; x < LINES_WIDTH; x++) {
			grid[y][x] = grid_ref[y][x];
			counter++;
		}
	}

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
	int lines_to_clear[4] = { 0,0,0,0 };
	int lines_count = 0;

	for (int y = LINES_HEIGHT - 1; y > 0; y--) {
		int count = 0;
		for (int x = 0; x < LINES_WIDTH; x++) {
			if (grid[y][x] != 0) {
				if (++count == LINES_WIDTH) {
					// Found non zero line
					lines_to_clear[lines_count] = y;
					lines_count++;

					// Clear entire line
					for (int xx = 0; xx < LINES_WIDTH; xx++) {
						// grid[y][xx] = 0;
					}
				}
			}
		}
	}

	if (lines_count > 0) {
		for (int y = lines_to_clear[0]; y >= 0; y--) {
			for (int x = 0; x < LINES_WIDTH; x++) {
				bool found = false;
				for (int i = 0; i < lines_count; i++) {
					if (lines_to_clear[i] == y) {
						found = true;
						break;
					}
				}
				LOGF("FOUND %d %d %d\n", y, x, found);
				grid[y + found + 1][x] = grid[y][x];
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

