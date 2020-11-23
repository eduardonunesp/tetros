#ifndef BUTTON_H
#define BUTTON_H

#include "types.h"

typedef struct game_s game_t;
typedef struct button_s button_t;

typedef void (*on_button_down_t)(const button_t*);
typedef void (*on_button_up_t  )(const button_t*);

typedef struct button_cbs_s {
	on_button_down_t on_btn_down;
	on_button_up_t   on_btn_up;
} button_cbs_t;

typedef struct button_s {
	SDL_Rect rect;

	int32_t     n_id;
	char* s_id;
	bool    is_down;
	bool    is_up;
	void*   data;

	button_cbs_t btn_cbs;
} button_t;

/**
 * \brief Creates new button with params x, y and w, h
 * \param x The X position relative on screen area
 * \param y The Y position relative on screen area
 * \param w The Width area of the button
 * \param h The Height area of the button
 * \return Button object ready to be used
 */
button_t*
button_create(int32_t x, int32_t y, int32_t w, int32_t h);

void
button_process_event(button_t *btn, const SDL_Event *ev);

void 
button_draw(const button_t *btn, const game_t *game);

#endif // BUTTON_H
