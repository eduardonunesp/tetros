#ifndef __SCENE_MENU_H__
#define __SCENE_MENU_H__

typedef struct scene_menu {

} scene_menu_t;

scene_menu_t* scene_menu_create();
void scene_menu_init(scene_menu_t* scene_menu);
void scene_menu_loop(scene_menu_t* scene_menu);
void scene_menu_destroy(scene_menu_t* scene_menu);

#endif // __SCENE_MENU_H__
