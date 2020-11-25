#include "tetris.h"

int get_random_piece() {
	return rand() % (N_TETROMINOS)+1;
}

tetromino_t* create_from_next(tetromino_t* tetromino) {
	tetromino_t* new_tetromino = (tetromino_t*)malloc(sizeof(tetromino_t));

	for (int i = 0; i < PIECE_VARIATIONS; i++) {
		for (int y = 0; y < PIECE_AREA_Y; y++) {
			for (int x = 0; x < PIECE_AREA_X; x++) {
				new_tetromino->piece[i][y][x] = tetromino->piece[i][y][x];
			}
		}
	}

	new_tetromino->variation = tetromino->variation;
	new_tetromino->x = INITIAL_POSITION_X;
	new_tetromino->y = INITIAL_POSITION_Y;
	new_tetromino->pinned = false;
	new_tetromino->color = tetromino->color;
	new_tetromino->type = tetromino->type;

	return new_tetromino;
}

tetromino_t* create_tetromino(int tetromino_type, int x, int y) {
	tetromino_t* new_tetromino = (tetromino_t*)malloc(sizeof(tetromino_t));
	new_tetromino->variation = 0;
	new_tetromino->x = x;
	new_tetromino->y = y;
	new_tetromino->pinned = false;
	new_tetromino->type = tetromino_type;

	new_tetromino->color.a = 255;
	new_tetromino->color.r = 255;
	new_tetromino->color.g = 255;
	new_tetromino->color.b = 255;

	switch (tetromino_type) {
	case TST:
	{
		new_tetromino->color.r = 0;
		new_tetromino->color.g = 255;
		new_tetromino->color.b = 255;

		int p1[PIECE_AREA_X][PIECE_AREA_Y] = TST0;
		int p2[PIECE_AREA_X][PIECE_AREA_Y] = TST1;
		int p3[PIECE_AREA_X][PIECE_AREA_Y] = TST0;
		int p4[PIECE_AREA_X][PIECE_AREA_Y] = TST1;

		for (int y = 0; y < PIECE_AREA_X; y++) {
			for (int x = 0; x < PIECE_AREA_X; x++) {
				new_tetromino->piece[0][y][x] = p1[y][x];
				new_tetromino->piece[1][y][x] = p2[y][x];
				new_tetromino->piece[2][y][x] = p3[y][x];
				new_tetromino->piece[3][y][x] = p4[y][x];
			}
		}
	}
	break;
	case TET:
	{
		new_tetromino->color.r = 255;
		new_tetromino->color.g = 0;
		new_tetromino->color.b = 255;

		int p1[PIECE_AREA_X][PIECE_AREA_Y] = TET0;
		int p2[PIECE_AREA_X][PIECE_AREA_Y] = TET1;
		int p3[PIECE_AREA_X][PIECE_AREA_Y] = TET2;
		int p4[PIECE_AREA_X][PIECE_AREA_Y] = TET3;

		for (int y = 0; y < PIECE_AREA_X; y++) {
			for (int x = 0; x < PIECE_AREA_X; x++) {
				new_tetromino->piece[0][y][x] = p1[y][x];
				new_tetromino->piece[1][y][x] = p2[y][x];
				new_tetromino->piece[2][y][x] = p3[y][x];
				new_tetromino->piece[3][y][x] = p4[y][x];
			}
		}
	}
	break;
	case TSW:
	{
		new_tetromino->color.r = 255;
		new_tetromino->color.g = 0;
		new_tetromino->color.b = 0;

		int p1[PIECE_AREA_X][PIECE_AREA_Y] = TSW0;
		int p2[PIECE_AREA_X][PIECE_AREA_Y] = TSW1;
		int p3[PIECE_AREA_X][PIECE_AREA_Y] = TSW0;
		int p4[PIECE_AREA_X][PIECE_AREA_Y] = TSW1;

		for (int y = 0; y < PIECE_AREA_X; y++) {
			for (int x = 0; x < PIECE_AREA_X; x++) {
				new_tetromino->piece[0][y][x] = p1[y][x];
				new_tetromino->piece[1][y][x] = p2[y][x];
				new_tetromino->piece[2][y][x] = p3[y][x];
				new_tetromino->piece[3][y][x] = p4[y][x];
			}
		}
	}
	break;
	case TSWI:
	{
		new_tetromino->color.r = 255;
		new_tetromino->color.g = 0;
		new_tetromino->color.b = 0;

		int p1[PIECE_AREA_X][PIECE_AREA_Y] = TSWI0;
		int p2[PIECE_AREA_X][PIECE_AREA_Y] = TSWI1;
		int p3[PIECE_AREA_X][PIECE_AREA_Y] = TSWI0;
		int p4[PIECE_AREA_X][PIECE_AREA_Y] = TSWI1;

		for (int y = 0; y < PIECE_AREA_X; y++) {
			for (int x = 0; x < PIECE_AREA_X; x++) {
				new_tetromino->piece[0][y][x] = p1[y][x];
				new_tetromino->piece[1][y][x] = p2[y][x];
				new_tetromino->piece[2][y][x] = p3[y][x];
				new_tetromino->piece[3][y][x] = p4[y][x];
			}
		}
	}
	break;
	case TSQ:
	{
		new_tetromino->color.r = 255;
		new_tetromino->color.g = 255;
		new_tetromino->color.b = 0;

		int p1[PIECE_AREA_X][PIECE_AREA_Y] = TSQ0;
		int p2[PIECE_AREA_X][PIECE_AREA_Y] = TSQ0;
		int p3[PIECE_AREA_X][PIECE_AREA_Y] = TSQ0;
		int p4[PIECE_AREA_X][PIECE_AREA_Y] = TSQ0;

		for (int y = 0; y < PIECE_AREA_X; y++) {
			for (int x = 0; x < PIECE_AREA_X; x++) {
				new_tetromino->piece[0][y][x] = p1[y][x];
				new_tetromino->piece[1][y][x] = p2[y][x];
				new_tetromino->piece[2][y][x] = p3[y][x];
				new_tetromino->piece[3][y][x] = p4[y][x];
			}
		}
	}
	break;
	case TEL:
	{
		new_tetromino->color.r = 0;
		new_tetromino->color.g = 0;
		new_tetromino->color.b = 255;

		int p1[PIECE_AREA_X][PIECE_AREA_Y] = TEL0;
		int p2[PIECE_AREA_X][PIECE_AREA_Y] = TEL1;
		int p3[PIECE_AREA_X][PIECE_AREA_Y] = TEL2;
		int p4[PIECE_AREA_X][PIECE_AREA_Y] = TEL3;

		for (int y = 0; y < PIECE_AREA_X; y++) {
			for (int x = 0; x < PIECE_AREA_X; x++) {
				new_tetromino->piece[0][y][x] = p1[y][x];
				new_tetromino->piece[1][y][x] = p2[y][x];
				new_tetromino->piece[2][y][x] = p3[y][x];
				new_tetromino->piece[3][y][x] = p4[y][x];
			}
		}
	}
	break;
	default:
		return NULL;
	}

	return new_tetromino;
}

void draw_next_tetromino(SDL_Renderer* renderer) {
	for (int y = 0; y < PIECE_AREA_Y; y++) {
		for (int x = 0; x < PIECE_AREA_X; x++) {
			if (next_tetromino && next_tetromino->piece[next_tetromino->variation][y][x] != 0) {
				SDL_SetRenderDrawColor(renderer,
					next_tetromino->color.r,
					next_tetromino->color.g,
					next_tetromino->color.b,
					SDL_ALPHA_OPAQUE
				);

				SDL_Rect rect = {
					(next_tetromino->x + x) * CELL_SIZE,
					(next_tetromino->y + y) * CELL_SIZE,
					CELL_SIZE, CELL_SIZE,
				};

				SDL_RenderFillRect(renderer, &rect);
				SDL_RenderDrawRect(renderer, &rect);
			}
		}
	}
}

void draw_tetromino(SDL_Renderer* renderer) {
	for (int y = 0; y < PIECE_AREA_Y; y++) {
		for (int x = 0; x < PIECE_AREA_X; x++) {
			if (curr_tetromino && curr_tetromino->piece[curr_tetromino->variation][y][x] != 0) {
				SDL_SetRenderDrawColor(renderer,
					curr_tetromino->color.r,
					curr_tetromino->color.g,
					curr_tetromino->color.b,
					SDL_ALPHA_OPAQUE
				);

				SDL_Rect rect = {
					GRID_X_OFFSET + ((curr_tetromino->x + x) * CELL_SIZE),
					GRID_Y_OFFSET + ((curr_tetromino->y + y) * CELL_SIZE),
					CELL_SIZE, CELL_SIZE,
				};

				SDL_RenderFillRect(renderer, &rect);
				SDL_RenderDrawRect(renderer, &rect);
			}
		}
	}
}

void update_tetromino() {
	if (curr_tetromino && curr_tetromino->pinned) {
		for (int y = 0; y < PIECE_AREA_Y; y++) {
			for (int x = 0; x < PIECE_AREA_X; x++) {
				if (curr_tetromino && curr_tetromino->piece[curr_tetromino->variation][y][x] != 0) {
					grid[curr_tetromino->y + y][curr_tetromino->x + x] = -curr_tetromino->type;
				}
			}
		}

		free(curr_tetromino);
		curr_tetromino = NULL;
		return;
	}


	for (int y = 0; y < PIECE_AREA_Y; y++) {
		for (int x = 0; x < PIECE_AREA_X; x++) {
			if (curr_tetromino && curr_tetromino->piece[curr_tetromino->variation][y][x] != 0) {
				if (curr_tetromino->y + y + 1 >= LINES_HEIGHT) {
					curr_tetromino->pinned = true;
					return;
				}

				if (grid[curr_tetromino->y + y + 1][curr_tetromino->x + x] != 0) {
					curr_tetromino->pinned = true;
					return;
				}
			}
		}
	}

	if (curr_tetromino) {
		curr_tetromino->y++;
	}
}

bool can_move_right() {
	for (int y = 0; y < PIECE_AREA_Y; y++) {
		for (int x = 0; x < PIECE_AREA_X; x++) {
			if (curr_tetromino && curr_tetromino->piece[curr_tetromino->variation][y][x] != 0) {
				if (curr_tetromino->x + x + 1 >= LINES_WIDTH) {
					return false;
				}

				if (grid[curr_tetromino->y + y][curr_tetromino->x + x + 1] != 0) {
					return false;
				}
			}
		}
	}

	return true;
}

bool can_move_left() {
	for (int y = 0; y < PIECE_AREA_Y; y++) {
		for (int x = 0; x < PIECE_AREA_X; x++) {
			if (curr_tetromino && curr_tetromino->piece[curr_tetromino->variation][y][x] != 0) {
				if (curr_tetromino->x + x - 1 < 0) {
					return false;
				}

				if (grid[curr_tetromino->y + y][curr_tetromino->x + x - 1] != 0) {
					return false;
				}
			}
		}
	}

	return true;
}

bool can_rotate() {
	if (!curr_tetromino) {
		return false;
	}

	int next_variation = curr_tetromino->variation + 1;
	if (next_variation >= PIECE_VARIATIONS) {
		next_variation = 0;
	}

	for (int y = 0; y < PIECE_AREA_Y; y++) {
		for (int x = 0; x < PIECE_AREA_X; x++) {
			if (curr_tetromino && curr_tetromino->piece[next_variation][y][x] != 0) {
				if (curr_tetromino->y + y >= LINES_HEIGHT) {
					return false;
				}

				if (curr_tetromino->x + x >= LINES_WIDTH) {
					return false;
				}

				if (curr_tetromino->x + x < 0) {
					return false;
				}

				if (grid[curr_tetromino->y + y][curr_tetromino->x + x] != 0) {
					return false;
				}
			}
		}
	}

	return true;
}
