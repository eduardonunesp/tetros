#ifndef GAME_H
#define GAME_H

#include "types.h"

#include "status.h"
#include "utils.h"
#include "assets/assets.h"

#include "scene.h"
#include "scenes/scene_menu/scene_menu.h"
#include "scenes/scene_play/scene_play.h"
#include "scenes/scene_end/scene_end.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define GAME_TITLE    "Tetros"
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 640
#define INITIAL_SCENE 1

COUNTABLE_ENUM(
	game_scenes_e,
	GAME_SCENE_MENU,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
);

typedef struct game_params_s {
	bool    no_fall;
	bool    grid_lines;
	int32_t fall_speed;
	int32_t start_level;
} game_params_t;

typedef struct game_s {
	SDL_Window*   win;
	SDL_Renderer* rdr;

	bool is_init;
	bool is_running;

	game_params_t    game_params;
	assets_images_t* asset_imgs;
	assets_font_t*   asset_fonts;

	scene_t* scenes[ENUM_COUNT(game_scenes_e)];
} game_t;

status_e
game_set_scene(game_scenes_e new_scn);

status_e
game_dispatch_event(int32_t ev_code, const void* data1, const void* data2);

#endif // GAME_H
