#include "game.h"
#include "log.h"
#include "utils.h"

game_t* game_create() {
	LOG("Creating game...");
	game_t* new_game = (game_t*)malloc(sizeof(game_t));

	ASSERT((new_game == NULL), "Failed to create game core");

	new_game->running = false;
	new_game->win = NULL;
	new_game->renderer = NULL;
	new_game->scene_menu = scene_menu_create();
	new_game->scene_play = scene_play_create();

	game_set_scene(new_game, GAME_SCENE_PLAY);

	LOG("Game created");
	return new_game;
}

void game_set_scene(game_t* game, game_scenes_e new_scene) {
	ASSERT((game == NULL), "Invalid game structure on switch scene");

	if (new_scene != game->active_scene) {
		LOGF("Switch scene %d\n", new_scene);
		game->active_scene = new_scene;
	}
}

void game_init(game_t* game) {
	LOG("Inializing...");
	ASSERT((game == NULL), "Invalid game structure on init");

	srand(time(0));

	ASSERT((SDL_Init(SDL_INIT_VIDEO) != 0), "Failed to init SDL2 libs");

	game->win = SDL_CreateWindow(GAME_TITLE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	ASSERT((game->win == NULL), "Invalid window structure");

	game->renderer = SDL_CreateRenderer(game->win, -1, SDL_RENDERER_ACCELERATED);
	ASSERT((game->renderer == NULL), "Invalid renderer structure");

	scene_menu_init(game);
	scene_play_init(game);

	LOG("Game initialized");
}

void handle_events(game_t* game) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (game->active_scene) {
		case GAME_SCENE_NONE:
			break;
		case GAME_SCENE_MENU:
			scene_menu_handle_events(game, &event);
			break;
		case GAME_SCENE_PLAY:
			scene_play_handle_events(game, &event);
			break;
		}
	}
}

void handle_update(game_t* game) {
	switch (game->active_scene) {
	case GAME_SCENE_NONE:
		break;
	case GAME_SCENE_MENU:
		scene_menu_handle_update(game);
		break;
	case GAME_SCENE_PLAY:
		scene_play_handle_update(game);
		break;
	}
}

void handle_rendering(game_t* game) {
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	SDL_RenderClear(game->renderer);

	switch (game->active_scene) {
	case GAME_SCENE_NONE:
		break;
	case GAME_SCENE_MENU:
		scene_menu_rendering(game);
		break;
	case GAME_SCENE_PLAY:
		scene_play_rendering(game);
		break;
	}

	SDL_RenderPresent(game->renderer);
}

void game_loop(game_t* game) {
	LOG("Running game");
	ASSERT((game == NULL), "Invalid game structure on loop");

	game->running = true;

	while (game->running) {
		handle_events(game);
		handle_update(game);
		handle_rendering(game);
	}
}

void game_destroy(game_t* game) {
	LOG("Game stopped");
	ASSERT((game == NULL), "Invalid game structure on destroy");
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->win);
	SDL_Quit();

	free(game->scene_menu);
	game->scene_menu = NULL;
	free(game->scene_play);
	game->scene_play = NULL;

	LOG("Game shutdown gracefuly");
}
