#ifndef __GAME_H__
#define __GAME_H__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define GAME_TITLE "Tetris"
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640

typedef struct game {
	SDL_Window* win;
	SDL_Renderer* renderer;
	bool running;
} game_t;

game_t* game_create();
void game_init(game_t* game);
void game_loop(game_t* game);
void game_destroy(game_t* game);

#endif // __GAME_H__
