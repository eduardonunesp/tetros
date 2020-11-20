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
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SEGMENT_WIDTH 40
#define SEGMENT_HEIGHT 40

bool running = true;
bool dead = false;
SDL_Window* win = NULL;
SDL_Renderer* renderer = NULL;

int main(int argc, char* argv[]) {
	srand(time(0));
	win = SDL_CreateWindow(GAME_TITLE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

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
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	LOG("Game end, bye!\n");

	return 0;
}
