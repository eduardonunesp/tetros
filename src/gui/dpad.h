#ifndef DPAD_H
#define DPAD_H

#include <SDL2/SDL.h>
#include "button.h"

#define BUTTON_SQR_SIZE 30
#define PROCESS_DELAY 100

typedef struct game_s game_t;
typedef struct dpad_s dpad_t;

typedef enum {
	DPAD_LEFT  = 'L',
	DPAD_RIGHT = 'R',
	DPAD_UP    = 'U',
	DPAD_DOWN  = 'D'
} dpad_dir_e;

typedef void (*on_dpad_down_t)(dpad_t*, dpad_dir_e);
typedef void (*on_dpad_up_t  )(dpad_t*, dpad_dir_e);

typedef struct dpad_cbs_s {
	on_dpad_down_t on_dpad_down;
	on_dpad_up_t   on_dpad_up;
} dpad_cbs_t;

typedef struct dpad_s {
	button_t* left;
	button_t* right;
	button_t* up;
	button_t* down;

	dpad_cbs_t dpad_cbs;
} dpad_t;

dpad_t*
dpad_create(int32_t x, int32_t y);

void
dpad_process_event(dpad_t* dpad, const SDL_Event* ev);

void
dpad_draw(dpad_t* dpad, const game_t* game);

#endif // DPAD_H
