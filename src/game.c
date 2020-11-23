#include "game.h"
#include "log.h"

static game_t* _game = NULL;
static game_scenes_e _curr_scn = INITIAL_SCENE;

status_e
game_set_scene(game_scenes_e new_scn)
{
	if (new_scn != _curr_scn) {
		LOGF("Switch scene %d\n", new_scn);
		scene_exit(_game->scenes[_curr_scn], _game);
		scene_enter(_game->scenes[new_scn], _game);
		_curr_scn = new_scn;

		return STATUS_SUCCESS;
	}

	return STATUS_NO_CHANGES;
}

status_e
game_dispatch_event(int32_t ev_code, const void* data1, const void* data2)
{
	LOGF("Dispatch event %d\n", ev_code);

	SDL_Event ev;
	SDL_zero(ev);

	ev.type = ev_code;
	ev.user.code = ev_code;
	ev.user.data1 = (void*)data1;
	ev.user.data2 = (void*)data2;
	SDL_PushEvent(&ev);

	return STATUS_SUCCESS;
}

void
game_init()
{
	LOG("Inializing...");

	srand(time(0));

	ASSERT((SDL_Init(SDL_INIT_VIDEO) != 0), "Failed to init SDL2 libs");

	_game->win = SDL_CreateWindow(GAME_TITLE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	ASSERT((_game->win == NULL), "Invalid window structure");

	_game->rdr = SDL_CreateRenderer(_game->win, -1, SDL_RENDERER_ACCELERATED);
	ASSERT((_game->rdr == NULL), "Invalid renderer structure");

	assets_images_init(_game);
	assets_font_init(_game);

	for (uint32_t scn_idx = 0; scn_idx < ENUM_COUNT(game_scenes_e); scn_idx++)
		scene_init(_game->scenes[scn_idx], _game);

	_game->is_init = true;
	LOG("Game initialized");
}

void
handle_events()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
		scene_event(_game->scenes[_curr_scn], _game, &event);
}

void
handle_update()
{
	scene_update(_game->scenes[_curr_scn], _game);
}

void
handle_rendering()
{
	SDL_SetRenderDrawColor(_game->rdr, 0, 0, 0, 255);
	SDL_RenderClear(_game->rdr);
	scene_render(_game->scenes[_curr_scn], _game);
	SDL_RenderPresent(_game->rdr);
}

void
game_loop()
{
#ifndef __EMSCRIPTEN__
	LOG("Running game");
	ASSERT((_game == NULL), "Invalid game structure on loop");
#endif

	_game->is_running = true;
#ifndef __EMSCRIPTEN__
	while (_game->is_running) {
#endif
		handle_events();
		handle_update();
		handle_rendering();
#ifndef __EMSCRIPTEN__
	}
#endif
}

void
game_destroy()
{
	LOG("Game destroy");
	ASSERT((_game == NULL), "Invalid game structure on destroy");

	for (uint32_t scn_idx = 0; scn_idx < ENUM_COUNT(game_scenes_e); scn_idx++) {
		scene_destroy(_game->scenes[scn_idx], _game);
		DESTROY(_game->scenes[scn_idx]);
	}

	assets_destroy(_game);
	DESTROY(_game->asset_imgs);

	SDL_DestroyRenderer(_game->rdr);
	SDL_DestroyWindow(_game->win);
	SDL_Quit();

	LOG("Game shutdown gracefuly");
}

void
game_create(int32_t argc, char* argv[])
{
	LOG("Creating game...");

	_game = NEW(game_t);

	ASSERT((_game == NULL), "Failed to create game core");

	_game->win = NULL;
	_game->rdr = NULL;
	_game->is_running = false;
	_game->is_init = false;
	_game->asset_imgs = assets_images_create();
	_game->asset_fonts = assets_font_create();

	_game->scenes[0] = scene_menu_create(_game);
	_game->scenes[1] = scene_play_create(_game);
	_game->scenes[2] = scene_end_create(_game);

	game_params_t game_params = {
		false, // no_fall
		false, // grid_lines
		1000,  // fall_speed
		0,     // start_level
	};

	_game->game_params = game_params;

	int32_t opt;
	while ((opt = getopt(argc, argv, "ns:gl:")) != -1) {
		switch (opt) {
#ifdef _DEBUG
		case 's':
		_game->game_params.fall_speed = atoi(optarg);
		break;
		case 'n': _game->game_params.no_fall = true; break;
		case 'g': _game->game_params.grid_lines = true; break;
		case 'l':
		_game->game_params.start_level = atoi(optarg);
		break;
#endif
		default:
		break;
		}
	}

	LOGF("Game param no fall %d\n", _game->game_params.no_fall);
	LOGF("Game param fall speed %d\n", _game->game_params.fall_speed);

	LOG("Game created");
}

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

void
iterate()
{
	game_loop();
}

#endif

int32_t
main(int32_t argc, char** argv)
{
	game_create(argc, argv);
	game_init();

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(iterate, 0, 1);
#else
	game_loop();
#endif

#ifdef __EMSCRIPTEN__
	emscripten_cancel_main_loop();
#endif

	game_destroy();
	return 0;
}
