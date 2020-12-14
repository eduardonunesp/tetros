#include "scene_menu.h"
#include "../log.h"
#include "../utils.h"

scene_menu_t* scene_menu_create() {
	LOG("Creating game menu scene...");
	scene_menu_t* new_scene = (scene_menu_t*)malloc(sizeof(scene_menu_t));

	ASSERT((new_scene == NULL), "Failed to create scene game menu");

	LOG("Game menu scene created");
	return new_scene;
}

void scene_menu_init(scene_menu_t* scene_menu) {

}

void scene_menu_loop(scene_menu_t* scene_menu) {

}

void scene_menu_destroy(scene_menu_t* scene_menu) {

}
