#ifndef SCENE_H
#define SCENE_H

#include "types.h"

typedef struct game_s game_t;
typedef struct scene_s scene_t;

typedef void (*on_scene_init_t   )(scene_t*, game_t*                  );
typedef void (*on_scene_enter_t  )(scene_t*, game_t*                  );
typedef void (*on_scene_event_t  )(scene_t*, game_t*, const SDL_Event*);
typedef void (*on_scene_update_t )(scene_t*, game_t*                  );
typedef void (*on_scene_render_t )(scene_t*, game_t*                  );
typedef void (*on_scene_exit_t   )(scene_t*, game_t*                  );
typedef void (*on_scene_destroy_t)(scene_t*, game_t*                  );

typedef struct scene_s {
	list_t* sprites;
	list_t* fonts;
	game_t* game;

	on_scene_init_t    on_init;
	on_scene_enter_t   on_enter;
	on_scene_event_t   on_event;
	on_scene_update_t  on_update;
	on_scene_render_t  on_render;
	on_scene_exit_t    on_exit;
	on_scene_destroy_t on_destroy;
} scene_t;

scene_t*
scene_create();

void
scene_add_sprite(scene_t* scn, int32_t x, int32_t y, int32_t w, int32_t h, SDL_Texture* tex);

void
scene_add_font(
	scene_t* scn, int32_t x, int32_t y, int32_t w, int32_t h,
	char* text, uint8_t r, uint8_t g, uint8_t b, TTF_Font* ttf);

void
scene_init(scene_t* scn, game_t* game);

void
scene_enter(scene_t* scn, game_t* game);

void
scene_event(scene_t* scn, game_t* game, const SDL_Event* ev);

void
scene_update(scene_t* scn, game_t* game);

void
scene_render(scene_t* scn, game_t* game);

void
scene_exit(scene_t* scn, game_t* game);

void
scene_destroy(scene_t* scn, game_t* game);

#endif // SCENE_H
