#ifndef __STATE_H__
#define __STATE_H__

typedef enum {
	GAME_STATE_INIT,
	GAME_STATE_PLAY,
	GAME_STATE_PAUSE,
	GAME_STATE_RESUME,
	GAME_STATE_GAMEOVER,
} game_state_e;

typedef struct state {
	int score;
	game_state_e current_state;
} state_t;

state_t* state_create();

#endif // __STATE_H__
