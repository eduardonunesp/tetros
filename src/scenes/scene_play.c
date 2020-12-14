#include "scene_play.h"
#include "../log.h"
#include "../utils.h"

scene_play_t* scene_play_create() {
	LOG("Creating game play scene...");
	scene_play_t* new_scene = (scene_play_t*)malloc(sizeof(scene_play_t));

	ASSERT((new_scene == NULL), "Failed to create scene game play");

	LOG("Game play scene created");
	return new_scene;
}

void scene_play_init(scene_play_t* scene_play) {

}

void scene_play_loop(scene_play_t* scene_play) {

}

void scene_play_destroy(scene_play_t* scene_play) {

}
