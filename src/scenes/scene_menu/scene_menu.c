#include "scene_menu.h"
#include "scene.h"
#include "game.h"
#include "log.h"
#include "utils.h"

static scene_menu_t* _scene_menu;

static void
on_init(scene_t* scene, game_t* game) {
	LOG("Scene menu init");
	scene_add_sprite(scene, 0, 0, 380, 640, game->asset_imgs->background);
	scene_add_font(scene, 4, 40, 320, 80, "TETROS", 255, 255, 0, game->asset_fonts->nokia_font);
	scene_add_font(scene, 6, 42, 318, 78, "TETROS", 255, 0, 0, game->asset_fonts->nokia_font);
	scene_add_font(scene, 2, 200, 318, 20, "Press Enter to Start", 0, 0, 0, game->asset_fonts->nokia_font);
}

static void
on_event(scene_t* scene, game_t* game, const SDL_Event* event) {
	if (event->type == SDL_QUIT)
		game->is_running = false;

	if (event->type == SDL_KEYUP) {
		if (event->key.keysym.sym == SDLK_ESCAPE)
			game->is_running = false;

		if (event->key.keysym.sym == SDLK_RETURN)
			game_set_scene(GAME_SCENE_PLAY);
	}
}

static void
on_update(scene_t* scene, game_t* game) {}

static void
on_render(scene_t* scene, game_t* game) {}

static void
on_destroy(scene_t* scene, game_t* game) {
	LOG("Scene menu destroy");
}

scene_t*
scene_menu_create(game_t* game) {
	LOG("Creating game menu scene...");

	_scene_menu = NEW(scene_menu_t);

	ASSERT((_scene_menu == NULL), "Failed to create scene structure menu");

	scene_t* new_scene = scene_create();

	ASSERT((new_scene == NULL), "Failed to create scene game menu");

	new_scene->on_init    = on_init;
	new_scene->on_enter   = NULL;
	new_scene->on_event   = on_event;
	new_scene->on_update  = on_update;
	new_scene->on_render  = on_render;
	new_scene->on_exit    = NULL;
	new_scene->on_destroy = on_destroy;

	LOG("Game menu scene created");
	return new_scene;
}
