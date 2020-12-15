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

	new_scene->curr_tetro = NULL;
	new_scene->last_time = 0;
	new_scene->current_time = 0;

	LOG("Game play scene created");
	return new_scene;
}

void scene_play_init(game_t* game) {
	LOG("Scene play init");
	grid_print(game->scene_play->grid);
	game->scene_play->current_time = SDL_GetTicks();
}

void scene_play_handle_events(game_t* game, SDL_Event* event) {
	if (event->type == SDL_QUIT) {
		LOG("Close window pressed");
		game->running = false;
	}

	if (event->type == SDL_KEYUP) {
		if (event->key.keysym.sym == SDLK_ESCAPE) {
			LOG("Escape button pressed");
			game->running = false;
		}

#ifdef _DEBUG
		if (!game->scene_play->curr_tetro) {
			int key_code = event->key.keysym.sym;

			// Only key numbers 1 to 6
			if (key_code >= 49 && key_code <= 54) {
				int tetro_type = key_code - 49;
				LOGF("Created debug tetro %d\n", tetro_type);
				tetro_t* new_tetro = tetro_create(tetro_type);

				game->scene_play->curr_tetro = new_tetro;
				tetro_print(new_tetro);
			}
		}
		else {
			if (event->key.keysym.sym == SDLK_0) {
				if (game->scene_play->curr_tetro) {
					free(game->scene_play->curr_tetro);
					game->scene_play->curr_tetro = NULL;
				}
			}
		}
	}
#endif
}

void render_grid(game_t* game) {
	grid_t* grid = game->scene_play->grid;
	SDL_Renderer* renderer = game->renderer;

	for (int y = 0;y <= grid->rows; y++) {
		for (int x = 0;x <= grid->cols; x++) {
			SDL_SetRenderDrawColor(renderer, GRID_DEBUG_COLOR);
			SDL_RenderDrawLine(renderer,
				grid->pos_x + (x * grid->cell_size),
				grid->pos_y,
				grid->pos_x + (x * grid->cell_size),
				grid->pos_y + (grid->rows * grid->cell_size)
			);

			SDL_SetRenderDrawColor(renderer, GRID_DEBUG_COLOR);
			SDL_RenderDrawLine(renderer,
				grid->pos_x,
				grid->pos_y + (y * grid->cell_size),
				grid->pos_x + (grid->cols * grid->cell_size),
				grid->pos_y + (y * grid->cell_size)
			);
		}
	}
}

void draw_tetro(game_t* game) {
	grid_t* grid = game->scene_play->grid;
	SDL_Renderer* renderer = game->renderer;
	tetro_t* tetro = game->scene_play->curr_tetro;

	for (int y = 0; y < TETRO_SQR_AREA; y++) {
		for (int x = 0; x < TETRO_SQR_AREA; x++) {
			if (tetro && tetro->data[tetro->curr_variation][y][x] != 0) {
				SDL_SetRenderDrawColor(renderer,
					tetro->color.r,
					tetro->color.g,
					tetro->color.b,
					SDL_ALPHA_OPAQUE
				);

				SDL_Rect rect = {
					grid->pos_x + ((tetro->grid_x + x) * CELL_SIZE),
					grid->pos_y + ((tetro->grid_y + y) * CELL_SIZE),
					CELL_SIZE, CELL_SIZE,
				};

				SDL_RenderFillRect(renderer, &rect);
				SDL_RenderDrawRect(renderer, &rect);
			}
		}
	}
}

void handle_tick_update(game_t* game) {
	LOG("TICK");
}

void scene_play_handle_update(game_t* game) {
	game->scene_play->current_time = SDL_GetTicks();
	if (game->scene_play->current_time > game->scene_play->last_time + TIME_SECOND) {
		handle_tick_update(game);
		game->scene_play->last_time = game->scene_play->current_time;
	}
}

void scene_play_rendering(game_t* game) {
#ifdef _DEBUG
	render_grid(game);
#endif
	draw_tetro(game);
}

void scene_play_destroy(game_t* game) {
	LOG("Scene play destroy");
}
