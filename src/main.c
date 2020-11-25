#include <SDL2/SDL.h>
#include <stdbool.h>
#include "tetris.h"

extern tetromino_t* curr_tetromino;
extern tetromino_t* next_tetromino;
extern int accelerate;


SDL_Window* win = NULL;
SDL_Renderer* renderer = NULL;
bool running = true;

int main(int argc, char* argv[]) {
	accelerate = 0;
	srand(time(0));
	win = SDL_CreateWindow(GAME_TITLE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	init_grid();

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

			parse_input(&event);
		}

		clear_line();

		current_time = SDL_GetTicks();
		if (!curr_tetromino || current_time > last_time + accelerate) {
			if (!curr_tetromino) {
				curr_tetromino = create_from_next(next_tetromino);
				free(next_tetromino);
				next_tetromino = NULL;
				next_tetromino = create_tetromino(get_random_piece(), NEXT_TETROMINO_X, NEXT_TETROMINO_Y);
			}
			update_tetromino();
			last_time = current_time + SPEED;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		draw_grid(renderer);
		draw_tetromino(renderer);
		draw_next_tetromino(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	LOG("Game end, bye!\n");

	return 0;
}
