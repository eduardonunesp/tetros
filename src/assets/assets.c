#include <SDL2/SDL_image.h>
#include "assets.h"
#include "../game.h"
#include "../utils.h"

#ifndef __EMSCRIPTEN__
#include "images/grid_bg.h"
#include "images/block.h"
#include "images/background.h"
#include "images/button_left.h"
#include "images/button_right.h"
#include "fonts/nokiafc22.h"
#endif

#ifdef __EMSCRIPTEN__
#define IMAGE_ASSET_LOAD(NAME) \
char *f_##NAME = "resources/images/"#NAME".png"; \
LOGF("Load file %s\n", f_##NAME); \
SDL_Surface * tmp_surface_##NAME = IMG_Load(f_##NAME); \
ASSERT((tmp_surface_##NAME == NULL), "Failed to load resource (null surface)"); \
SDL_Texture* loaded_##NAME = SDL_CreateTextureFromSurface(game->rdr, tmp_surface_##NAME); \
SDL_FreeSurface(tmp_surface_##NAME);
#else
#define IMAGE_ASSET_LOAD(NAME) \
SDL_RWops* rw_##NAME = SDL_RWFromConstMem(NAME, sizeof(NAME)); \
LOGF("Loaded %lu for file %s bytes\n", sizeof(NAME), #NAME); \
ASSERT((rw_##NAME == NULL), "Failed to load resource"); \
SDL_Surface* tmp_surface_##NAME = IMG_Load_RW(rw_##NAME, 1); \
ASSERT((tmp_surface_##NAME == NULL), "Failed to load resource (null surface)"); \
SDL_Texture* loaded_##NAME = SDL_CreateTextureFromSurface(game->rdr, tmp_surface_##NAME); \
SDL_FreeSurface(tmp_surface_##NAME);
#endif

#ifdef __EMSCRIPTEN__
#define TTF_ASSET_LOAD(NAME) \
char *f_##NAME = "resources/fonts/"#NAME".ttf"; \
LOGF("Load file %s\n", f_##NAME); \
TTF_Font* loaded_##NAME = TTF_OpenFont(f_##NAME, 42); \
ASSERT((loaded_##NAME == NULL), "Failed to load resource (null surface)");
#else
#define TTF_ASSET_LOAD(NAME) \
SDL_RWops* rw_##NAME = SDL_RWFromConstMem(NAME, sizeof(NAME)); \
LOGF("Loaded %lu for file %s bytes\n", sizeof(NAME), #NAME); \
ASSERT((rw_##NAME == NULL), "Failed to load resource"); \
TTF_Font* loaded_##NAME = TTF_OpenFontRW(rw_##NAME, 1, 42); \
ASSERT((loaded_##NAME == NULL), "Failed to load resource (null surface)");
#endif

assets_images_t*
assets_images_create()
{
	LOG("Creating asset images...");

	ASSERT((IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG), "Failed to init SDL Image");

	assets_images_t* assets_images = NEW(assets_images_t);

	ASSERT((assets_images == NULL), "Failed to create asset images");
	memset(assets_images, 0, sizeof(assets_images_t));

	LOG("Asset images created");
	return assets_images;
}

assets_font_t*
assets_font_create()
{
	LOG("Creating asset ttf...");

	ASSERT((TTF_Init() != 0), "Failed to init SDL TTF");

	assets_font_t* asset_fonts = NEW(assets_font_t);
	memset(asset_fonts, 0, sizeof(assets_font_t));
	return asset_fonts;
}

void
assets_images_init(const game_t* game)
{
	IMAGE_ASSET_LOAD(grid_bg);
	game->asset_imgs->grid_bg = loaded_grid_bg;

	IMAGE_ASSET_LOAD(block);
	game->asset_imgs->block = loaded_block;

	IMAGE_ASSET_LOAD(background);
	game->asset_imgs->background = loaded_background;

	IMAGE_ASSET_LOAD(button_left);
	game->asset_imgs->button_left = loaded_button_left;

	IMAGE_ASSET_LOAD(button_right);
	game->asset_imgs->button_right = loaded_button_right;

	LOGF("%s\n", IMG_GetError());
}

void
assets_font_init(const game_t* game)
{
	TTF_ASSET_LOAD(nokiafc22);
	game->asset_fonts->nokia_font = loaded_nokiafc22;

	LOGF("%s\n", TTF_GetError());
}

void
assets_destroy(const game_t* game)
{
#ifdef __EMSCRIPTEN__
	DESTROY(game->asset_imgs->button_right);
	DESTROY(game->asset_imgs->button_left);
	DESTROY(game->asset_imgs->background);
	DESTROY(game->asset_imgs->block);
	DESTROY(game->asset_imgs->grid_bg);
#endif
}
