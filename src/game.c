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

void game_loop(game_t* game) {
	LOG("Running game");
	ASSERT((game == NULL), "Invalid game structure on loop");

	game->running = true;

	while (game->running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				game->running = false;
			}
		}
	}
}

void game_destroy(game_t* game) {
	LOG("Game stopped");
	ASSERT((game == NULL), "Invalid game structure on destroy");
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->win);
	SDL_Quit();
	LOG("Game shutdown gracefuly");
}
