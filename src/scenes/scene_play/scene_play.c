#include <SDL2/SDL_image.h>
#include "scene.h"
#include "font.h"
#include "scene_play.h"
#include "game.h"
#include "log.h"
#include "utils.h"

static scene_play_t* _scene_play = NULL;
static int32_t           _last_time;
static int32_t           _current_time;

// static void
// on_dpad_button_down(dpad_t* dpad, dpad_dir_e dir)
// {
// 	if (!_scene_play->curr_tetro)
// 		return;

// 	LOGF("Dir %d\n", dir);

// 	switch (dir) {
// 	case DPAD_RIGHT:
// 		tetro_move_sideways(_scene_play->curr_tetro, TETRO_MOVE_RIGHT, _scene_play->grid);
// 		break;
// 	case DPAD_LEFT:
// 		tetro_move_sideways(_scene_play->curr_tetro, TETRO_MOVE_LEFT, _scene_play->grid);
// 		break;
// 	case DPAD_DOWN:
// 		tetro_update_fall(_scene_play->curr_tetro, _scene_play->grid, _scene_play);
// 		break;
// 	default:
// 	break;
// 	}
// }

// static void
// on_button_rotate_l(const button_t* btn)
// {
// 	if (_scene_play->curr_tetro)
// 		tetro_rotate(_scene_play->curr_tetro, TETRO_ROTATE_CW, _scene_play->grid);
// }

// static void
// on_button_rotate_r(const button_t* btn)
// {
// 	if (_scene_play->curr_tetro)
// 		tetro_rotate(_scene_play->curr_tetro, TETRO_ROTATE_CCW, _scene_play->grid);
// }
static void
set_score(scene_t* scn, uint32_t score)
{
	_scene_play->score += score;
	char buffer[10];
	sprintf(buffer, "%06d", _scene_play->score);

	LOGF("%s\n", buffer);
	font_t* f = list_at(scn->fonts, 2);
	font_text(f, buffer);
}

static void
set_level(scene_t* scn, uint32_t level)
{
	_scene_play->level += level;
	char buffer[10];
	sprintf(buffer, "%06d", _scene_play->level);

	LOGF("%s\n", buffer);
	font_t* f = list_at(scn->fonts, 4);
	font_text(f, buffer);
}

static void
on_init(scene_t* scn, game_t* game)
{
	LOG("Scene play init");
	_scene_play->game = game;

	grid_print(_scene_play->grid);
	// _scene_play->dpad->dpad_cbs.on_dpad_down = on_dpad_button_down;
	// _scene_play->rotate_r->btn_cbs.on_btn_down = on_button_rotate_r;
	// _scene_play->rotate_l->btn_cbs.on_btn_down = on_button_rotate_l;

	scene_add_sprite(scn, 0, 0, 380, 640, game->asset_imgs->background);
	scene_add_sprite(scn, GRID_POSX - 5, GRID_POSY - 5, (CELL_SIZE * COLS_NUMBER) + 10, (CELL_SIZE * ROWS_NUMBER) + 10, game->asset_imgs->grid_bg);

	scene_add_font(scn, 2, 500, SCREEN_WIDTH, 20, "Press Enter To Start", RGB_BLACK, game->asset_fonts->nokia_font);

	scene_add_font(scn, 240, 120, 80, 10, "SCORE", RGB_BLACK, game->asset_fonts->nokia_font);
	scene_add_font(scn, 240, 130, 80, 10, "000000", RGB_BLACK, game->asset_fonts->nokia_font);

	scene_add_font(scn, 240, 160, 80, 10, "LEVEL", RGB_BLACK, game->asset_fonts->nokia_font);
	scene_add_font(scn, 240, 170, 80, 10, "000000", RGB_BLACK, game->asset_fonts->nokia_font);

	set_score(scn, 0);
	set_level(scn, _scene_play->game->game_params.start_level);

	if (!game->game_params.no_fall)
		grid_clear_line(_scene_play->grid);
}

static void
scene_set_state(scene_state_e new_state)
{
	if (new_state != _scene_play->state) {
		LOGF("New scene state %d\n", new_state);
		_scene_play->state = new_state;
	}
}

static void
add_tetro_to_game(game_t *game)
{
	tetro_t* new_tetro = _scene_play->next_tetro;
	_scene_play->curr_tetro = new_tetro;
	tetro_reset(new_tetro);
	tetro_reset(_scene_play->curr_tetro);
	_scene_play->next_tetro = tetro_create(tetro_take_piece());
	_scene_play->stats[_scene_play->curr_tetro->tetro_type]++;
	grid_print(_scene_play->grid);
}

static void
scene_ready(scene_t* scn, game_t* game)
{
	grid_clear(_scene_play->grid);
	set_score(scn, 0);
	set_level(scn, _scene_play->game->game_params.start_level);
	add_tetro_to_game(game);
	font_t* font = (font_t*) list_at(scn->fonts, 0);
	font->active = false;
	_current_time = SDL_GetTicks();
	scene_set_state(SCENE_STATE_PLAYING);
}

static void
scene_game_over(scene_t* scn, game_t* game)
{
	font_t* font = (font_t*) list_at(scn->fonts, 0);
	font->active = true;
	font_text(font, "Press R To Restart");
}

static void
on_scene_event_waiting(game_t* game, const SDL_Event* ev)
{
	if (ev->type == SDL_KEYUP)
		if (ev->key.keysym.sym == SDLK_RETURN)
			scene_set_state(SCENE_STATE_READY);
}

static void
on_scene_event_playing(game_t* game, const SDL_Event* ev)
{
	if (ev->type == SDL_USEREVENT) {
		LOGF("User event arrived %d\n", ev->type);
		if (ev->type == _scene_play->play_events.EVENT_TETRO_PINNED) {
			DESTROY(_scene_play->curr_tetro);
			add_tetro_to_game(game);
		}
	}

	if (ev->type == SDL_KEYDOWN && _scene_play->curr_tetro) {
		if (ev->key.keysym.sym == SDLK_DOWN || ev->key.keysym.sym == SDLK_s)
			tetro_update_fall(_scene_play->curr_tetro, _scene_play->grid, _scene_play);

		if (ev->key.keysym.sym == SDLK_RIGHT || ev->key.keysym.sym == SDLK_d)
			tetro_move_sideways(_scene_play->curr_tetro, TETRO_MOVE_RIGHT, _scene_play->grid);

		if (ev->key.keysym.sym == SDLK_LEFT || ev->key.keysym.sym == SDLK_a)
			tetro_move_sideways(_scene_play->curr_tetro, TETRO_MOVE_LEFT, _scene_play->grid);

		if (ev->key.keysym.sym == SDLK_PERIOD)
			tetro_rotate(_scene_play->curr_tetro, TETRO_ROTATE_CCW, _scene_play->grid);

		if (ev->key.keysym.sym == SDLK_COMMA)
			tetro_rotate(_scene_play->curr_tetro, TETRO_ROTATE_CW, _scene_play->grid);
	}
}

static void
on_scene_event_gameover(game_t* game, const SDL_Event* ev)
{
	if (ev->type == SDL_KEYUP)
		if (ev->key.keysym.sym == SDLK_r)
			scene_set_state(SCENE_STATE_READY);
}

static void
on_event(scene_t* scene, game_t* game, const SDL_Event* ev)
{
	if (ev->type == SDL_QUIT) {
		LOG("Close window pressed");
		game->is_running = false;
	}

	// button_process_event(_scene_play->rotate_l, ev);
	// button_process_event(_scene_play->rotate_r, ev);
	
	if (_scene_play->state == SCENE_STATE_WAITING)
		on_scene_event_waiting(game, ev);

	if (_scene_play->state == SCENE_STATE_PLAYING)
		on_scene_event_playing(game, ev);

	if (_scene_play->state == SCENE_STATE_GAMEOVER)
		on_scene_event_gameover(game, ev);

	if (ev->type == SDL_KEYUP) {
#ifdef _DEBUG
		if (ev->key.keysym.sym == SDLK_ESCAPE) {
			LOG("Escape button pressed");
			game->is_running = false;
		}

		if (ev->key.keysym.sym == SDLK_g)
			grid_print(_scene_play->grid);

		if (ev->key.keysym.sym == SDLK_c) {
			grid_print(_scene_play->grid);
			grid_clear_line(_scene_play->grid);
			grid_print(_scene_play->grid);
		}

		if (!_scene_play->curr_tetro) {
			int32_t key_code = ev->key.keysym.sym;

			// Only key numbers 1 to 7
			if (key_code >= 49 && key_code <= 55) {
				int32_t tetro_type = key_code - 48;
				LOGF("Created debug tetro %d\n", tetro_type);
				tetro_t* new_tetro = tetro_create(tetro_type);
				_scene_play->curr_tetro = new_tetro;
			}
		} else {
			if (ev->key.keysym.sym == SDLK_0)
				if (_scene_play->curr_tetro)
					DESTROY(_scene_play->curr_tetro);
		}
#endif
	}
}

static void
on_scene_update_waiting(game_t* game)
{
}

static void
on_scene_update_playing(scene_t* scn, game_t* game)
{
	if (!game->game_params.no_fall) {
		uint32_t lines = grid_clear_line(_scene_play->grid);
		if (lines > 0) {
			set_score(scn, 10);
			if (_scene_play->score >=_scene_play->next_level) {
				_scene_play->next_level += 100;
				set_level(scn, 1);
			}
		}	
	}

	if (is_grid_full(_scene_play->grid))
		scene_set_state(SCENE_STATE_GAMEOVER);

	_current_time = SDL_GetTicks();
	if (_current_time > _last_time + (game->game_params.fall_speed - (_scene_play->level * 50))) {
		if (_scene_play->curr_tetro)
			tetro_update_fall(_scene_play->curr_tetro, _scene_play->grid, _scene_play);
		_last_time = _current_time;
	}
}

static void
on_update(scene_t* scn, game_t* game)
{
	// dpad_process_event(_scene_play->dpad, NULL);

	switch(_scene_play->state) {
	case SCENE_STATE_WAITING:
		on_scene_update_waiting(game);
		break;
	case SCENE_STATE_READY:
		scene_ready(scn, game);
		break;
	case SCENE_STATE_PLAYING: {
		on_scene_update_playing(scn, game);
		break;
	}
	case SCENE_STATE_PAUSE:
		break;
	case SCENE_STATE_RESUME:
		break;
	case SCENE_STATE_GAMEOVER:
		scene_game_over(scn, game);
		break;
	}
}

// DRAW -----

static void
draw_grid(game_t* game)
{
	grid_t* grid = _scene_play->grid;

#ifdef _DEBUG
	SDL_Renderer* renderer = game->rdr;
	if (game->game_params.grid_lines) {
		for (int32_t y = 0;y <= grid->rows; y++) {
			for (int32_t x = 0;x <= grid->cols; x++) {
				SDL_SetRenderDrawColor(renderer, GRID_DEBUG_COLOR);
				SDL_RenderDrawLine(renderer,
					grid->x + (x * grid->cell_size),
					grid->y,
					grid->x + (x * grid->cell_size),
					grid->y + (grid->rows * grid->cell_size)
				);

				SDL_SetRenderDrawColor(renderer, GRID_DEBUG_COLOR);
				SDL_RenderDrawLine(renderer,
					grid->x,
					grid->y + (y * grid->cell_size),
					grid->x + (grid->cols * grid->cell_size),
					grid->y + (y * grid->cell_size)
				);
			}
		}
	}
#endif

	for (int32_t y = 0;y < grid->rows; y++) {
		for (int32_t x = 0;x < grid->cols; x++) {
			int32_t cell = _scene_play->grid->data[y][x];
			if (cell < 0 && cell > -10) {
				SDL_Color color = TETRO_COLORS[grid->data[y][x] * -1];
				SDL_SetTextureColorMod(
					game->asset_imgs->block,
					color.r, color.g, color.b
				);

				SDL_Rect rect = {
					grid->x + (x * CELL_SIZE), grid->y + (y * CELL_SIZE),
					CELL_SIZE, CELL_SIZE,
				};

				SDL_RenderCopy(game->rdr, game->asset_imgs->block, NULL, &rect);
			}
		}
	}
}

static void
draw_tetro(game_t* game)
{
	grid_t* grid = _scene_play->grid;
	tetro_t* tetro = _scene_play->curr_tetro;

	for (int32_t y = 0; y < TETRO_SQR_AREA; y++) {
		for (int32_t x = 0; x < TETRO_SQR_AREA; x++) {
			if (tetro && tetro->data[tetro->curr_rotate][y][x] != 0) {
				SDL_SetTextureColorMod(
					game->asset_imgs->block,
					tetro->color.r,
					tetro->color.g,
					tetro->color.b
				);

				SDL_Rect rect = {
					grid->x + ((tetro->grid_x + x) * CELL_SIZE),
					grid->y + ((tetro->grid_y + y) * CELL_SIZE),
					CELL_SIZE, CELL_SIZE,
				};

				SDL_Rect s = { 0, 0, DRAW_SIZE, DRAW_SIZE };
				SDL_RenderCopy(game->rdr, game->asset_imgs->block, &s, &rect);
			}
		}
	}
}

static void
draw_next_tetro(game_t* game)
{
	tetro_t* tetro = _scene_play->next_tetro;

	for (int32_t y = 0; y < TETRO_SQR_AREA; y++) {
		for (int32_t x = 0; x < TETRO_SQR_AREA; x++) {
			if (tetro && tetro->data[0][y][x] != 0) {
				SDL_SetTextureColorMod(
					game->asset_imgs->block,
					tetro->color.r,
					tetro->color.g,
					tetro->color.b
				);

				SDL_Rect rect = {
					NEXT_POSX + ((tetro->grid_x + x) * CELL_SIZE),
					NEXT_POSY + ((tetro->grid_y + y) * CELL_SIZE),
					CELL_SIZE, CELL_SIZE,
				};

				// TODO: Fix image size w, h => 24, 24
				SDL_Rect s = { 0, 0, DRAW_SIZE, DRAW_SIZE };
				SDL_RenderCopy(game->rdr, game->asset_imgs->block, &s, &rect);
			}
		}
	}
}

static void
on_render(scene_t* scene, game_t* game)
{
	draw_grid(game);
	draw_tetro(game);
	draw_next_tetro(game);

	// dpad_draw(_scene_play->dpad, game);
	// button_draw(_scene_play->rotate_l, game);
	// button_draw(_scene_play->rotate_r, game);
}

static void
on_destroy(scene_t* scene, game_t* game)
{
	LOG("Scene play destroy");
}

scene_t*
scene_play_create(game_t* game)
{
	LOG("Creating game play scene...");

	_scene_play = NEW(scene_play_t);

	ASSERT((_scene_play == NULL), "Failed to create scene game play");

	_scene_play->grid = grid_create(GRID_POSX, GRID_POSY, CELL_SIZE);

	play_events_s events = {
		SDL_RegisterEvents(1000),
	};

	_scene_play->curr_tetro  = NULL;
	_scene_play->play_events = events;
	_scene_play->dpad        = dpad_create(DPAD_POS);
	// _scene_play->rotate_l    = button_create(BTN_RL_POS, 30, 30);
	// _scene_play->rotate_r    = button_create(BTN_RR_POS, 30, 30);
	_scene_play->next_tetro  = tetro_create(tetro_take_piece());
	_scene_play->state       = SCENE_STATE_WAITING;
	// _scene_play->state       = SCENE_STATE_GAMEOVER;
	
	_scene_play->score      = 0;
	_scene_play->level      = 0;
	_scene_play->next_level = 100;

	memset(&_scene_play->stats, 0, sizeof(_scene_play->stats));

	scene_t* new_scene = scene_create();

	ASSERT((new_scene == NULL), "Failed to create scene game play");

	new_scene->on_init    = on_init;
	new_scene->on_enter   = NULL;
	new_scene->on_event   = on_event;
	new_scene->on_update  = on_update;
	new_scene->on_render  = on_render;
	new_scene->on_exit    = NULL;
	new_scene->on_destroy = on_destroy;

	LOG("Game play scene created");
	return new_scene;
}
