#ifndef __GAME_H__
#define __GAME_H__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include "state.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_play.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define GAME_TITLE "Tetros"
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640

typedef struct game {
	SDL_Window* win;
	SDL_Renderer* renderer;
	bool running;
	unsigned int last_time;
	unsigned int current_time;
	state_t* state;
	scene_menu_t* scene_menu;
	scene_play_t* scene_play;
} game_t;

game_t* game_create();
void game_init(game_t* game);
void game_loop(game_t* game);
void game_destroy(game_t* game);

#endif // __GAME_H__