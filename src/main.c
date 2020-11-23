#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "pieces.h"

#ifdef _DEBUG
#define LOG(msg) printf(msg);
#define LOGF(fmt, ...) fprintf(stdout, fmt, __VA_ARGS__)
#else
#define LOG(fmt)
#define LOGF(fmt, ...)
#endif

#define GAME_TITLE "Tetris"
#define GAME_TITLE_DEAD "Tetris (DEAD)"

#define LINES_WIDTH 10
#define LINES_HEIGHT 20
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640
#define GRID_X_OFFSET 116
#define GRID_Y_OFFSET 60
#define PIECE_AREA 4
#define PIECE_VARS 4
#define CELL_SIZE 24
#define LINE_OFFSET 1
#define SPEED 1500
#define MOVE_RIGHT 1
#define MOVE_LEFT -1
#define ROTATE 10

bool running = true;
bool dead = false;
bool can_rotate = true;

int grid[LINES_HEIGHT][LINES_WIDTH] = {
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},

	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
	{-1, -1, -1, -1, 0,  0, 0, 0, 0, 0},
};

typedef struct {
	int piece_type;
	bool fixit;
	int x, y;
	int curr_var;
	int piece[PIECE_VARS][PIECE_AREA][PIECE_AREA];
} current_piece_t;

current_piece_t* curr_piece = NULL;
SDL_Window* win = NULL;
SDL_Renderer* renderer = NULL;

void draw_grid_lines(SDL_Renderer* renderer) {
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
}

void draw_grid(SDL_Renderer* renderer) {
	for (int y = 0; y < LINES_HEIGHT; y++) {
		for (int x = 0; x < LINES_WIDTH; x++) {
			int piece = grid[y][x];

			// Negative numbers for pieces fixed
			if (piece < 0) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

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

bool check_action(int action_type) {
	for (int y = 0; y < PIECE_AREA; y++) {
		for (int x = 0; x < PIECE_AREA; x++) {
			if (curr_piece->piece[curr_piece->curr_var][y][x] != 0) {
				switch (action_type)
				{
				case MOVE_LEFT:
					if (curr_piece->x - 1 < 0 || grid[curr_piece->y + y][curr_piece->x + x + 1] != 0) {
						return false;
					}
					break;

				case MOVE_RIGHT:
					if (curr_piece->x >= LINES_WIDTH - 1 || grid[curr_piece->y + y][curr_piece->x + x - 1] != 0) {
						return false;
					}
					break;

				default:
					break;
				}
			}
		}
	}

	return true;
}

bool check_rotate() {
	if (!can_rotate) {
		return false;
	}

	int curr_var = curr_piece->curr_var + 1;
	if (curr_var >= PIECE_VARS) {
		curr_var = 0;
	}

	for (int y = 0; y < PIECE_AREA; y++) {
		for (int x = 0; x < PIECE_AREA; x++) {
			if (curr_piece->piece[curr_var][y][x] != 0) {
				if (grid[curr_piece->y + y][curr_piece->x + x] < 0) {
					return false;
				}

				if (curr_piece->x - 1 < 0 || grid[curr_piece->y + y][curr_piece->x + x + 1] != 0) {
					return false;
				}

				if (curr_piece->x >= LINES_WIDTH - 1 || grid[curr_piece->y + y][curr_piece->x + x - 1] != 0) {
					return false;
				}
			}
		}
	}

	return true;
}

void update_current_piece() {
	if (!curr_piece) {
		return;
	}

	can_rotate = true;

	if (curr_piece->fixit) {
		for (int y = 0; y < PIECE_AREA; y++) {
			for (int x = 0; x < PIECE_AREA; x++) {
				if (curr_piece->piece[curr_piece->curr_var][y][x] != 0) {
					grid[curr_piece->y + y][curr_piece->x + x] = -curr_piece->piece_type;
					// LOGF("%d %d %d\n", curr_piece->y, curr_piece->x, -curr_piece->piece_type);
				}
			}
		}

		free(curr_piece);
		curr_piece = NULL;
		return;
	}

	curr_piece->y++;

	for (int y = 0; y < PIECE_AREA; y++) {
		for (int x = 0; x < PIECE_AREA; x++) {
			if (curr_piece->piece[curr_piece->curr_var][y][x] != 0) {
				if (grid[curr_piece->y + y][curr_piece->x + x] < 0) {
					can_rotate = false;
				}

				if (grid[curr_piece->y + y + 1][curr_piece->x] < 0) {
					curr_piece->fixit = true;
					can_rotate = false;
				}

				if (curr_piece->y + y + 1 >= LINES_HEIGHT) {
					curr_piece->fixit = true;
					can_rotate = false;
				}
			}
		}
	}
}

void draw_current_piece(SDL_Renderer* rendered) {
	if (!curr_piece) {
		return;
	}

	for (int y = 0; y < PIECE_AREA; y++) {
		for (int x = 0; x < PIECE_AREA; x++) {
			if (curr_piece->piece[curr_piece->curr_var][y][x] != 0) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

				SDL_Rect rect = {
					GRID_X_OFFSET + ((curr_piece->x + x) * CELL_SIZE),
					GRID_Y_OFFSET + ((curr_piece->y + y) * CELL_SIZE),
					CELL_SIZE, CELL_SIZE,
				};

				SDL_RenderFillRect(renderer, &rect);
				SDL_RenderDrawRect(renderer, &rect);
			}
		}
	}
}

void create_piece(int piece_type) {
	curr_piece = (current_piece_t*)malloc(sizeof(current_piece_t));
	curr_piece->curr_var = 0;
	curr_piece->x = 0;
	curr_piece->y = 0;
	curr_piece->fixit = false;
	curr_piece->piece_type = piece_type;

	switch (piece_type) {
	case TST:
	{
		int p1[PIECE_AREA][PIECE_AREA] = TST0;
		int p2[PIECE_AREA][PIECE_AREA] = TST1;
		int p3[PIECE_AREA][PIECE_AREA] = TST0;
		int p4[PIECE_AREA][PIECE_AREA] = TST1;

		for (int y = 0; y < PIECE_AREA; y++) {
			for (int x = 0; x < PIECE_AREA; x++) {
				curr_piece->piece[0][y][x] = p1[y][x];
				curr_piece->piece[1][y][x] = p2[y][x];
				curr_piece->piece[2][y][x] = p3[y][x];
				curr_piece->piece[3][y][x] = p4[y][x];
			}
		}
	}
	break;
	case TET:
	{
		int p1[PIECE_AREA][PIECE_AREA] = TET0;
		int p2[PIECE_AREA][PIECE_AREA] = TET1;
		int p3[PIECE_AREA][PIECE_AREA] = TET2;
		int p4[PIECE_AREA][PIECE_AREA] = TET3;

		for (int y = 0; y < PIECE_AREA; y++) {
			for (int x = 0; x < PIECE_AREA; x++) {
				curr_piece->piece[0][y][x] = p1[y][x];
				curr_piece->piece[1][y][x] = p2[y][x];
				curr_piece->piece[2][y][x] = p3[y][x];
				curr_piece->piece[3][y][x] = p4[y][x];
			}
		}
	}
	break;
	case TSW:
	{
		int p1[PIECE_AREA][PIECE_AREA] = TSW0;
		int p2[PIECE_AREA][PIECE_AREA] = TSW1;
		int p3[PIECE_AREA][PIECE_AREA] = TSW0;
		int p4[PIECE_AREA][PIECE_AREA] = TSW1;

		for (int y = 0; y < PIECE_AREA; y++) {
			for (int x = 0; x < PIECE_AREA; x++) {
				curr_piece->piece[0][y][x] = p1[y][x];
				curr_piece->piece[1][y][x] = p2[y][x];
				curr_piece->piece[2][y][x] = p3[y][x];
				curr_piece->piece[3][y][x] = p4[y][x];
			}
		}
	}
	break;
	case TSQ:
	{
		int p1[PIECE_AREA][PIECE_AREA] = TSQ0;
		int p2[PIECE_AREA][PIECE_AREA] = TSQ0;
		int p3[PIECE_AREA][PIECE_AREA] = TSQ0;
		int p4[PIECE_AREA][PIECE_AREA] = TSQ0;

		for (int y = 0; y < PIECE_AREA; y++) {
			for (int x = 0; x < PIECE_AREA; x++) {
				curr_piece->piece[0][y][x] = p1[y][x];
				curr_piece->piece[1][y][x] = p2[y][x];
				curr_piece->piece[2][y][x] = p3[y][x];
				curr_piece->piece[3][y][x] = p4[y][x];
			}
		}
	}
	break;
	case TEL:
	{
		int p1[PIECE_AREA][PIECE_AREA] = TEL0;
		int p2[PIECE_AREA][PIECE_AREA] = TEL1;
		int p3[PIECE_AREA][PIECE_AREA] = TEL2;
		int p4[PIECE_AREA][PIECE_AREA] = TEL3;

		for (int y = 0; y < PIECE_AREA; y++) {
			for (int x = 0; x < PIECE_AREA; x++) {
				curr_piece->piece[0][y][x] = p1[y][x];
				curr_piece->piece[1][y][x] = p2[y][x];
				curr_piece->piece[2][y][x] = p3[y][x];
				curr_piece->piece[3][y][x] = p4[y][x];
			}
		}
	}
	break;
	default:
		break;
	}
}

int main(int argc, char* argv[]) {
	srand(time(0));
	win = SDL_CreateWindow(GAME_TITLE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	create_piece(TST);

	LOG("Game start\n");

	unsigned int last_time = 0, current_time;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}

			switch (event.type) {
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {

				case SDLK_UP:
				{
					if (curr_piece && check_rotate()) {
						curr_piece->curr_var++;
						if (curr_piece->curr_var >= PIECE_VARS) {
							curr_piece->curr_var = 0;
						}
					}
				}
				break;
				case SDLK_RIGHT:
				{
					if (curr_piece && check_action(MOVE_RIGHT)) {
						curr_piece->x++;
					}
				}
				break;
				case SDLK_LEFT:
				{
					if (curr_piece && check_action(MOVE_LEFT)) {
						curr_piece->x--;
					}
				}
				break;
				case SDLK_DOWN:
				{
					// curr_piece->y += CELL_SIZE;
				}
				break;
				default:
					break;
				}
			}
		}

		current_time = SDL_GetTicks();
		if (current_time > last_time && !dead) {
			update_current_piece();
			last_time = current_time + SPEED;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		draw_grid_lines(renderer);
		draw_current_piece(renderer);
		draw_grid(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	LOG("Game end, bye!\n");

	return 0;
}
