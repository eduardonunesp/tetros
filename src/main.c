#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

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

#define TST 0
#define TET 1
#define TSW 2
#define TSQ 3
#define TEL 4

// straight tetromino
#define TST0 {  \
	{0, 1, 0, 0}, \
	{0, 1, 0, 0}, \
	{0, 1, 0, 0}, \
	{0, 1, 0, 0}, \
}

#define TST1 {  \
	{0, 0, 0, 0}, \
	{1, 1, 1, 1}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
}

// T-tetromino
#define TET0 {  \
	{0, 2, 0, 0}, \
	{2, 2, 2, 0}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
}

#define TET1 {  \
	{0, 2, 0, 0}, \
	{0, 2, 2, 0}, \
	{0, 2, 0, 0}, \
	{0, 0, 0, 0}, \
}

#define TET2 {  \
	{0, 0, 0, 0}, \
	{2, 2, 2, 0}, \
	{0, 2, 0, 0}, \
	{0, 0, 0, 0}, \
}

#define TET3 {  \
	{0, 2, 0, 0}, \
	{2, 2, 0, 0}, \
	{0, 2, 0, 0}, \
	{0, 0, 0, 0}, \
}

// skew tetromino
#define TSW0 {  \
	{0, 3, 3, 0}, \
	{0, 0, 3, 3}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
}

// skew tetromino
#define TSW1 {  \
	{0, 0, 3, 0}, \
	{0, 3, 3, 0}, \
	{0, 3, 0, 0}, \
	{0, 0, 0, 0}, \
}

// square tetromino
#define TSQ0 {  \
	{0, 4, 4, 0}, \
	{0, 4, 4, 0}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
};

// L-tetromino
#define TEL0 {   \
	{0, 5, 0, 0}, \
	{0, 5, 0, 0}, \
	{0, 5, 5, 0}, \
	{0, 0, 0, 0}, \
};

#define TEL1 {   \
	{0, 0, 0, 0}, \
	{0, 5, 5, 5}, \
	{0, 5, 0, 0}, \
	{0, 0, 0, 0}, \
};

#define TEL2 {   \
	{5, 5, 0, 0}, \
	{0, 5, 0, 0}, \
	{0, 5, 0, 0}, \
	{0, 0, 0, 0}, \
};

#define TEL3 {   \
	{0, 0, 5, 0}, \
	{5, 5, 5, 0}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
};

bool running = true;
bool dead = false;

int grid[LINES_HEIGHT][LINES_WIDTH] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

typedef struct {
	int curr_var;
	int piece[PIECE_VARS][PIECE_AREA][PIECE_AREA];
} current_piece_t;

current_piece_t* curr_piece = NULL;
SDL_Window* win = NULL;
SDL_Renderer* renderer = NULL;

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
					x * CELL_SIZE, y * CELL_SIZE,
					CELL_SIZE, CELL_SIZE,
				};
				SDL_RenderDrawRect(renderer, &rect);
			}
		}
	}
}

void create_piece(int piece_type) {
	curr_piece = (current_piece_t*)malloc(sizeof(current_piece_t));
	curr_piece->curr_var = 0;

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

	create_piece(TEL);


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
					curr_piece->curr_var++;
					if (curr_piece->curr_var >= PIECE_VARS) {
						curr_piece->curr_var = 0;
					}
				}
				break;

				default:
					break;
				}
			}
		}

		current_time = SDL_GetTicks();
		if (current_time > last_time && !dead) {
			last_time = current_time + 500;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		// draw_grid(renderer);
		draw_current_piece(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	LOG("Game end, bye!\n");

	return 0;
}
