#ifndef FONT_H
#define FONT_H

#include "types.h"

typedef struct game_s game_t;

typedef struct font_s {
	SDL_Texture* tex;
	TTF_Font*    ttf;
	game_t*      game;

	char*   text;
	int32_t x, y;
	int32_t w, h;
	uint8_t r, g, b;

	bool active;
} font_t;

font_t*
font_create(
	int32_t x, int32_t y, int32_t w, int32_t h,
	char* text, uint8_t r, uint8_t g, uint8_t b,
	TTF_Font* ttf_font);

void
font_init(font_t* font, game_t* game);

void
font_text(font_t* font, char* text);

void
font_update(font_t* font);

void
font_draw(font_t* font);

void
font_destroy(font_t* font);

#endif // FONT_H
