#include "dpad.h"
#include "game.h"
#include "log.h"
#include "utils.h"

static dpad_t* _dpad = NULL;
static uint32_t     _last_time;
static uint32_t     _current_time;

void
fn_button_pressed(const button_t* btn) 
{
	LOGF("DPad Button %c\n", btn->n_id);
	_dpad->dpad_cbs.on_dpad_down(_dpad, btn->n_id);
}

dpad_t*
dpad_create(int32_t x, int32_t y) 
{
	LOG("Creating dpad...");
	dpad_t* new_dpad = NEW(dpad_t);

	ASSERT((new_dpad == NULL), "Failed to create dpad");

	_dpad = new_dpad;
	new_dpad->left  = button_create(x     , y     , BUTTON_SQR_SIZE, BUTTON_SQR_SIZE);
	new_dpad->right = button_create(x + 34, y     , BUTTON_SQR_SIZE, BUTTON_SQR_SIZE);
	new_dpad->up    = button_create(x + 18, y - 32, BUTTON_SQR_SIZE, BUTTON_SQR_SIZE);
	new_dpad->down  = button_create(x + 18, y + 32, BUTTON_SQR_SIZE, BUTTON_SQR_SIZE);

	new_dpad->left->n_id  = 'L';
	new_dpad->right->n_id = 'R';
	new_dpad->up->n_id    = 'U';
	new_dpad->down->n_id  = 'D';

	new_dpad->dpad_cbs.on_dpad_down = NULL;

	new_dpad->left->btn_cbs.on_btn_down  = fn_button_pressed;
	new_dpad->right->btn_cbs.on_btn_down = fn_button_pressed;
	new_dpad->down->btn_cbs.on_btn_down  = fn_button_pressed;
	new_dpad->up->btn_cbs.on_btn_down    = fn_button_pressed;
	_current_time = SDL_GetTicks();

	return new_dpad;
}

void
dpad_process_event(dpad_t* dpad, const SDL_Event* ev) 
{
	_current_time = SDL_GetTicks();
	if (_current_time > _last_time + PROCESS_DELAY) {
		button_process_event(dpad->left,  ev);
		button_process_event(dpad->right, ev);
		button_process_event(dpad->up,    ev);
		button_process_event(dpad->down,  ev);
		_last_time = _current_time;
	}
}

void
dpad_draw(dpad_t* dpad, const game_t* game)
{
	button_draw(dpad->left,  game);
	button_draw(dpad->right, game);
	button_draw(dpad->up,    game);
	button_draw(dpad->down,  game);
}
