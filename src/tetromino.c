#include "tetris.h"

tetromino_t* create_tetromino(int tetromino_type) {
	tetromino_t* new_tetromino = (tetromino_t*)malloc(sizeof(tetromino_t));
	new_tetromino->variation = 0;
	new_tetromino->x = 0;
	new_tetromino->y = 0;
	new_tetromino->pinned = false;
	new_tetromino->type = tetromino_type;

	switch (tetromino_type) {
	case TST:
	{
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
	case TSQ:
	{
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

void draw_tetromino(SDL_Renderer* renderer) {
	for (int y = 0; y < PIECE_AREA_Y; y++) {
		for (int x = 0; x < PIECE_AREA_X; x++) {
			if (curr_tetromino && curr_tetromino->piece[curr_tetromino->variation][y][x] != 0) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

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
	return true;
}

bool can_move_left() {
	return true;
}
