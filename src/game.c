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
	new_game->state = state_create();
	new_game->scene_menu = scene_menu_create();
	new_game->scene_play = scene_play_create();
	new_game->last_time = 0;
	new_game->current_time = 0;
	LOG("Game created");
	return new_game;
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
	LOG("Game initialized");
}

void handle_events(game_t* game) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			game->running = false;
		}

		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				game->running = false;
			}
		}
	}
}

void handle_tick_event(game_t* game) {
	if (game->state->current_state > GAME_STATE_INIT) {

	}
}

void handle_rendering(game_t* game) {
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	SDL_RenderClear(game->renderer);

	if (game->state->current_state == GAME_STATE_INIT) {
		scene_menu_loop(game->scene_menu);
	}

	if (game->state->current_state > GAME_STATE_INIT) {
		scene_play_loop(game->scene_play);
	}

	SDL_RenderPresent(game->renderer);
}

void game_loop(game_t* game) {
	LOG("Running game");
	ASSERT((game == NULL), "Invalid game structure on loop");

	game->running = true;
	game->current_time = SDL_GetTicks();

	while (game->running) {
		handle_events(game);

		game->current_time = SDL_GetTicks();
		if (game->current_time > game->last_time + TIME_SECOND) {
			handle_tick_event(game);
			game->last_time = game->current_time;
		}

		handle_rendering(game);
	}
}

void game_destroy(game_t* game) {
	LOG("Game stopped");
	ASSERT((game == NULL), "Invalid game structure on destroy");
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->win);
	SDL_Quit();

	free(game->state);
	game->state = NULL;
	free(game->scene_menu);
	game->scene_menu = NULL;
	free(game->scene_play);
	game->scene_play = NULL;

	LOG("Game shutdown gracefuly");
}
