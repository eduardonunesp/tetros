#include "scene_menu.h"
#include "../game.h"
#include "../log.h"
#include "../utils.h"

scene_menu_t* scene_menu_create() {
	LOG("Creating game menu scene...");
	scene_menu_t* new_scene = (scene_menu_t*)malloc(sizeof(scene_menu_t));

	ASSERT((new_scene == NULL), "Failed to create scene game menu");

	LOG("Game menu scene created");
	return new_scene;
}

void scene_menu_init(game_t* game) {
	LOG("Scene menu init");
}

void scene_menu_handle_events(game_t* game, SDL_Event* event) {
	if (event->type == SDL_QUIT) {
		game->running = false;
	}

	if (event->type == SDL_KEYUP) {
		if (event->key.keysym.sym == SDLK_ESCAPE) {
			game->running = false;
		}

		if (event->key.keysym.sym == SDLK_RETURN) {
			game_set_scene(game, GAME_SCENE_PLAY);
		}
	}
}

void scene_menu_handle_update(game_t* game) {

}

void scene_menu_rendering(game_t* game) {

}

void scene_menu_destroy(game_t* game) {
	LOG("Scene menu destroy");
}
