#ifndef SPRITE_H
#define SPRITE_H

#include "types.h"

typedef struct game_s game_t;

typedef struct sprite_s {
	SDL_Texture* tex;
	game_t*      game;

	int32_t x, y;
	int32_t w, h;

	bool active;
} sprite_t;

sprite_t*
sprite_create(int32_t x, int32_t y, int32_t w, int32_t h, SDL_Texture* tex);

void
sprite_init(sprite_t* spr, game_t* game);

void
sprite_move(sprite_t* spr, int32_t x, int32_t y);

void
sprite_color(sprite_t* spr, uint8_t r, uint8_t g, uint8_t b);

void
sprite_draw(sprite_t* spr);

#endif // SPRITE_H
