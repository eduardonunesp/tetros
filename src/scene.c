#include "scene.h"
#include "game.h"
#include "sprite.h"
#include "font.h"
#include "utils.h"


scene_t*
scene_create()
{
	scene_t* new_scene = NEW(scene_t);

	ASSERT((new_scene == NULL), "Failed to create new scene");

	new_scene->sprites = list_create();
	new_scene->fonts   = list_create();

	ASSERT((new_scene->sprites == NULL), "Failed to create new scene");

	return new_scene;
}

void
scene_add_sprite(scene_t* scn, int32_t x, int32_t y, int32_t w, int32_t h, SDL_Texture* tex)
{
	sprite_t* new_sprite = sprite_create(x, y, w, h, tex);
	sprite_init(new_sprite, scn->game);

	ASSERT((new_sprite == NULL), "Failed to create new sprite on scene");

	list_push(scn->sprites, (void*) new_sprite);
}

void
scene_add_font(
	scene_t* scn, int32_t x, int32_t y, int32_t w, int32_t h,
	char* text, uint8_t r, uint8_t g, uint8_t b, TTF_Font* ttf)
{
	font_t* new_font = font_create(x, y, w, h, text, r, g, b, ttf);
	font_init(new_font, scn->game);

	ASSERT((new_font == NULL), "Failed to create new font on scene");

	list_push(scn->fonts, (void*) new_font);
}

void
scene_init(scene_t* scn, game_t* game)
{
	scn->game = game;

	if (scn->on_init)
		scn->on_init(scn, game);
}

void
scene_enter(scene_t* scn, game_t* game)
{
	if (scn->on_enter)
		scn->on_enter(scn, game);
}

void
scene_event(scene_t* scn, game_t* game, const SDL_Event* ev)
{
	if (scn->on_event)
		scn->on_event(scn, game, ev);
}

void
scene_update(scene_t* scn, game_t* game)
{
	if (scn->on_update)
		scn->on_update(scn, game);
}

void
scene_render(scene_t* scn, game_t* game)
{
	if (scn->sprites->head) {
		node_t* curr = scn->sprites->head;

		while (curr != NULL) {
			sprite_t* s = (sprite_t*) curr->data;
			if (s != NULL) sprite_draw(s);
			curr = curr->next;
		}
	}

	if (scn->fonts->head) {
		node_t* curr = scn->fonts->head;

		while (curr != NULL) {
			font_t* f = (font_t*) curr->data;
			if (f != NULL) font_draw(f);
			curr = curr->next;
		}
	}

	if (scn->on_render)
		scn->on_render(scn, game);
}

void
scene_exit(scene_t* scn, game_t* game)
{
	if (scn->on_exit)
		scn->on_exit(scn, game);
}

void
scene_destroy(scene_t* scn, game_t* game)
{
	if(scn->on_destroy)
		scn->on_destroy(scn, game);
}
