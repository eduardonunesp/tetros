#include <SDL2/SDL.h>
#include <stdbool.h>
#include "tetris.h"

extern int accelerate;

SDL_Window* win = NULL;
SDL_Renderer* renderer = NULL;
bool running = true;

int main(int argc, char* argv[]) {
	srand(time(0));
	win = SDL_CreateWindow(GAME_TITLE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	tetromino_t* curr_tetromino = NULL;
	tetromino_t* next_tetromino = NULL;
	int accelerate;
	int grid[LINES_HEIGHT][LINES_WIDTH];

	init_grid(grid);

	curr_tetromino = create_tetromino(get_random_piece(), INITIAL_POSITION_X, INITIAL_POSITION_Y);
	next_tetromino = create_tetromino(get_random_piece(), NEXT_TETROMINO_X, NEXT_TETROMINO_Y);

	LOG("Game start\n");

	unsigned int last_time = 0, current_time;
	while (running) {
		accelerate = 0;

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}

			switch (event.type) {
			case SDL_KEYDOWN: {
				switch (event.key.keysym.sym) {
				case SDLK_DOWN:
				{
					accelerate = -1000;
				}
				break;
				case SDLK_UP:
				{
					if (curr_tetromino && can_rotate(grid, curr_tetromino)) {
						curr_tetromino->variation++;
						if (curr_tetromino->variation >= PIECE_VARIATIONS) {
							curr_tetromino->variation = 0;
						}
					}
				}
				break;
				case SDLK_RIGHT:
				{
					if (curr_tetromino && can_move_right(grid, curr_tetromino)) {
						curr_tetromino->x++;
					}
				}
				break;
				case SDLK_LEFT:
				{
					if (curr_tetromino && can_move_left(grid, curr_tetromino)) {
						curr_tetromino->x--;
					}
				}
				break;
				default:
					break;
				}
			}
			default:
				break;
			}
		}

		clear_line(grid);

		current_time = SDL_GetTicks();
		if (current_time > last_time + accelerate) {
			if (!curr_tetromino) {
				curr_tetromino = create_from_next(next_tetromino);
				tetromino_t* new_next_tetromino = create_tetromino(get_random_piece(), NEXT_TETROMINO_X, NEXT_TETROMINO_Y);
				free(next_tetromino);
				next_tetromino = NULL;
				next_tetromino = new_next_tetromino;
			}

			update_tetromino(grid, &curr_tetromino);
			last_time = current_time + SPEED;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		draw_grid(renderer, grid);
		draw_tetromino(renderer, curr_tetromino);
		draw_next_tetromino(renderer, next_tetromino);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	LOG("Game end, bye!\n");

	return 0;
}
