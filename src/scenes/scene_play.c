#include "scene_play.h"
#include "../game.h"
#include "../log.h"
#include "../utils.h"

scene_play_t* scene_play_create() {
	LOG("Creating game play scene...");
	scene_play_t* new_scene = (scene_play_t*)malloc(sizeof(scene_play_t));

	ASSERT((new_scene == NULL), "Failed to create scene game play");

	LOG("Game play scene created");
	return new_scene;
}

void scene_play_init(game_t* game) {
	LOG("Scene play init");
}

void scene_play_handle_events(game_t* game, SDL_Event* event) {
	if (event->type == SDL_QUIT) {
		game->running = false;
	}

	if (event->type == SDL_KEYDOWN) {
		if (event->key.keysym.sym == SDLK_ESCAPE) {
			game->running = false;
		}
	}
}

void scene_play_loop(game_t* game) {

}

void scene_play_destroy(game_t* game) {
	LOG("Scene play destroy");
}
