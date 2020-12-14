#include "state.h"
#include "log.h"
#include "utils.h"

state_t* state_create() {
	LOG("Creating state...");
	state_t* new_state = (state_t*)malloc(sizeof(state_t));

	ASSERT((new_state == NULL), "Failed to create game core");

	new_state->score = 0;
	new_state->current_state = GAME_STATE_INIT;
	LOG("State created");
	return new_state;
}
