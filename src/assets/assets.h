#ifndef ASSETS_H
#define ASSETS_H

#include "types.h"

typedef struct game_s game_t;

typedef struct assets_images_s {
	SDL_Texture* block;
	SDL_Texture* grid_bg;
	SDL_Texture* background;
	SDL_Texture* button_left;
	SDL_Texture* button_right;
} assets_images_t;

typedef struct assets_font_s {
	TTF_Font* nokia_font;
} assets_font_t;

assets_images_t*
assets_images_create();

assets_font_t*
assets_font_create();

void
assets_destroy(const game_t* game);

void
assets_images_init(const game_t* game);

void
assets_font_init(const game_t* game);

#endif // ASSETS_H
