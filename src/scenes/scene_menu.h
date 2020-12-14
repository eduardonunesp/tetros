#ifndef __SCENE_MENU_H__
#define __SCENE_MENU_H__

#include <SDL.h>

typedef struct game game_t;

typedef struct scene_menu {} scene_menu_t;

scene_menu_t* scene_menu_create();
void scene_menu_init(game_t* game);
void scene_menu_handle_events(game_t* game, SDL_Event* event);
void scene_menu_rendering(game_t* game);
void scene_menu_destroy(game_t* game);

#endif // __SCENE_MENU_H__
