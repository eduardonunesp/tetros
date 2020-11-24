#include <SDL2/SDL.h>
#include <stdbool.h>
#include "tetris.h"

extern tetromino_t* curr_tetromino;


SDL_Window* win = NULL;
SDL_Renderer* renderer = NULL;
bool running = true;

int main(int argc, char* argv[]) {
	srand(time(0));
	win = SDL_CreateWindow(GAME_TITLE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	init_grid();

	curr_tetromino = create_tetromino(TST);

	LOG("Game start\n");

	unsigned int last_time = 0, current_time;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}

			parse_input(&event);
		}

		current_time = SDL_GetTicks();
		if (current_time > last_time) {
			if (!curr_tetromino) {
				curr_tetromino = create_tetromino(TST);
			}
			update_tetromino();
			last_time = current_time + SPEED;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		draw_grid(renderer);
		draw_tetromino(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	LOG("Game end, bye!\n");

	return 0;
}
