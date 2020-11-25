#include "tetris.h"

void parse_input(SDL_Event* event) {
	switch (event->type) {
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_DOWN:
		{
			accelerate = -1000;
		}
		break;
		case SDLK_UP:
		{
			if (curr_tetromino && can_rotate()) {
				curr_tetromino->variation++;
				if (curr_tetromino->variation >= PIECE_VARIATIONS) {
					curr_tetromino->variation = 0;
				}
			}
		}
		break;
		case SDLK_RIGHT:
		{
			if (curr_tetromino && can_move_right()) {
				curr_tetromino->x++;
			}
		}
		break;
		case SDLK_LEFT:
		{
			if (curr_tetromino && can_move_left()) {
				curr_tetromino->x--;
			}
		}
		break;
		default:
			break;
		}
	}
}
