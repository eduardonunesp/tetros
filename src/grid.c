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

