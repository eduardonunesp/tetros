#ifndef __SCENE_PLAY_H__
#define __SCENE_PLAY_H__

typedef struct scene_play {

} scene_play_t;

scene_play_t* scene_play_create();
void scene_play_init(scene_play_t* scene_play);
void scene_play_loop(scene_play_t* scene_play);
void scene_play_destroy(scene_play_t* scene_play);


#endif // __SCENE_PLAY_H__
