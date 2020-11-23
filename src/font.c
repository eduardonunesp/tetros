#include "font.h"
#include "game.h"
#include "utils.h"
#include "log.h"

font_t*
font_create(
	int32_t x, int32_t y, int32_t w, int32_t h,
	char* text, uint8_t r, uint8_t g, uint8_t b,
	TTF_Font* ttf_font)
{
	font_t* new_font = NEW(font_t);

	ASSERT((new_font == NULL), "Failed to create font");

	new_font->tex  = NULL;
	new_font->ttf = ttf_font;
	new_font->game = NULL;

	new_font->text = text;
	new_font->x = x;
	new_font->y = y;
	new_font->h = h;
	new_font->w = w;
	new_font->r = r;
	new_font->g = g;
	new_font->b = b;

	new_font->active = true;

	return new_font;
}

void
font_init(font_t* font, game_t* game)
{
	font->game = game;
	SDL_Color color = { font->r, font->g , font->b };
	SDL_Surface* tmp_sf = TTF_RenderText_Solid(font->ttf, font->text, color);
	font->tex = SDL_CreateTextureFromSurface(game->rdr, tmp_sf);
	SDL_FreeSurface(tmp_sf);
}

void
font_text(font_t* font, char* text)
{
	font->text = text;
	SDL_Color color = { font->r, font->g , font->b };
	SDL_Surface* tmp_sf = TTF_RenderText_Solid(font->ttf, font->text, color);
	font->tex = SDL_CreateTextureFromSurface(font->game->rdr, tmp_sf);
	SDL_FreeSurface(tmp_sf);
}

void
font_draw(font_t* font)
{
	if (!font->active)
		return;

	SDL_Rect r = {font->x, font->y, font->w, font->h};
	SDL_RenderCopy(font->game->rdr, font->tex, NULL, &r);
}

void
font_destroy(font_t* font)
{
	TTF_CloseFont(font->ttf);
}
