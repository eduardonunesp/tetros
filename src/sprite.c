#include "sprite.h"
#include "game.h"
#include "utils.h"
#include "log.h"

sprite_t*
sprite_create(int32_t x, int32_t y, int32_t w, int32_t h, SDL_Texture* tex)
{
	sprite_t* new_sprite = NEW(sprite_t);

	ASSERT((new_sprite == NULL), "Failed to create sprite");

	new_sprite->tex  = tex;
	new_sprite->game = NULL;

	new_sprite->x = x;
	new_sprite->y = y;
	new_sprite->w = w;
	new_sprite->h = h;
	
	new_sprite->active = true;

	return new_sprite;
}

void
sprite_init(sprite_t* spr, game_t* game)
{
	spr->game = game;
}

void
sprite_move(sprite_t* spr, int32_t x, int32_t y)
{
	spr->x += x;
	spr->y += y;
}

void
sprite_color(sprite_t* spr, uint8_t r, uint8_t g, uint8_t b)
{
	SDL_SetTextureColorMod(spr->tex, r, g, b);
}

void
sprite_draw(sprite_t* spr)
{
	if (!spr->active)
		return;
	
	SDL_Rect r = {spr->x, spr->y, spr->w, spr->h};
	SDL_RenderCopy(spr->game->rdr, spr->tex, NULL, &r);
}
