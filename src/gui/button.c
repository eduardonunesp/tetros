#include "button.h"
#include "game.h"
#include "log.h"
#include "utils.h"

button_t*
button_create(int32_t x, int32_t y, int32_t w, int32_t h) 
{
	LOG("Creating button...");
	button_t* new_btn = NEW(button_t);

	ASSERT((new_btn == NULL), "Failed to create button");

	new_btn->rect    = (SDL_Rect) {x, y, h, w};
	new_btn->is_down = false;
	new_btn->is_up   = true;
	new_btn->is_down = NULL;
	new_btn->is_up   = NULL;

	return new_btn;
}

void
button_process_event(button_t *btn, const SDL_Event *ev) 
{
	int32_t x = 0;
	int32_t y = 0;

	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		if (
			x >= btn->rect.x &&
			x <= (btn->rect.x + btn->rect.w) &&
			y >= btn->rect.y &&
			y <= (btn->rect.y + btn->rect.h)) {

			if (btn->btn_cbs.on_btn_down) {
				btn->is_down = true;
				btn->btn_cbs.on_btn_down(btn);
			}
		}
	} else {
		if (btn->is_down) {
			btn->is_up = true;
			if (btn->btn_cbs.on_btn_up) {
				btn->btn_cbs.on_btn_up(btn);
			}
		}
	}
}

void 
button_draw(const button_t* btn, const game_t* game) 
{
	SDL_SetRenderDrawColor(game->rdr, 255, 0, 0, 255);
	SDL_RenderDrawRect(game->rdr, &btn->rect);
}
