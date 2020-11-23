#include "scene_end.h"
#include "scene.h"
#include "game.h"
#include "log.h"
#include "utils.h"

static scene_end_t* _scene_end;

void static
scene_end_init(scene_t* scene, game_t* game) {
	LOG("Scene end init");
}

void static
scene_end_handle_events(scene_t* scene, game_t* game, const SDL_Event* event) {
	if (event->type == SDL_QUIT)
		game->is_running = false;

	if (event->type == SDL_KEYUP) {
		if (event->key.keysym.sym == SDLK_ESCAPE)
			game->is_running = false;

		if (event->key.keysym.sym == SDLK_RETURN)
			game_set_scene(GAME_SCENE_PLAY);
	}
}

void static
scene_end_handle_update(scene_t* scene, game_t* game) {}

void static
scene_end_rendering(scene_t* scene, game_t* game) {}

void static
scene_end_destroy(scene_t* scene, game_t* game) {
	LOG("Scene end destroy");
}

scene_t*
scene_end_create(game_t* game) {
	LOG("Creating game end scene...");

	_scene_end = NEW(scene_end_t);

	ASSERT((_scene_end == NULL), "Failed to create scene structure end");

	scene_t* new_scene = scene_create();

	ASSERT((new_scene == NULL), "Failed to create scene game end");

	new_scene->on_init    = scene_end_init;
	new_scene->on_enter   = NULL;
	new_scene->on_event   = scene_end_handle_events;
	new_scene->on_update  = scene_end_handle_update;
	new_scene->on_render  = scene_end_rendering;
	new_scene->on_exit    = NULL;
	new_scene->on_destroy = scene_end_destroy;

	LOG("Game end scene created");
	return new_scene;
}
