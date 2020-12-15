#include "scene_play.h"
#include "../game.h"
#include "../log.h"
#include "../utils.h"

scene_play_t* scene_play_create() {
	LOG("Creating game play scene...");
	scene_play_t* new_scene = (scene_play_t*)malloc(sizeof(scene_play_t));

	ASSERT((new_scene == NULL), "Failed to create scene game play");

	new_scene->grid = grid_create(
		GRID_ROWS, GRID_COLS,
		GRID_POSX, GRID_POSY,
		CELL_SIZE
	);

	LOG("Game play scene created");
	return new_scene;
}

void scene_play_init(game_t* game) {
	LOG("Scene play init");
	grid_print(game->scene_play->grid);
}

void scene_play_handle_events(game_t* game, SDL_Event* event) {
	if (event->type == SDL_QUIT) {
		game->running = false;
	}

	if (event->type == SDL_KEYUP) {
		if (event->key.keysym.sym == SDLK_ESCAPE) {
			game->running = false;
		}

		if (event->key.keysym.sym == SDLK_t) {
			tetro_t* t = tetro_create(TETRO_STRAIGHT);
			tetro_print(t);
		}
	}
}

void scene_play_rendering(game_t* game) {
	grid_t* grid = game->scene_play->grid;
	SDL_Renderer* renderer = game->renderer;

	for (int y = 0;y <= grid->rows; y++) {
		for (int x = 0;x <= grid->cols; x++) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(renderer,
				grid->pos_x + (x * grid->cell_size),
				grid->pos_y,
				grid->pos_x + (x * grid->cell_size),
				grid->pos_y + (grid->rows * grid->cell_size)
			);

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(renderer,
				grid->pos_x,
				grid->pos_y + (y * grid->cell_size),
				grid->pos_x + (grid->cols * grid->cell_size),
				grid->pos_y + (y * grid->cell_size)
			);
		}
	}
}

void scene_play_destroy(game_t* game) {
	LOG("Scene play destroy");
}
