#include "tetro.h"
#include "../log.h"
#include "../utils.h"
#include "grid.h"

int TETRO_DATA[TETRO_TYPES][TETRO_VARIATIONS][TETRO_SQR_AREA][TETRO_SQR_AREA] = {
	{},
	// straight tetro
	{
		{
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 0, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 0, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
	},

	// T-tetro
	{
		{
			{0, 2, 0, 0},
			{2, 2, 2, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 2, 0, 0},
			{0, 2, 2, 0},
			{0, 2, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{2, 2, 2, 0},
			{0, 2, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 2, 0, 0},
			{2, 2, 0, 0},
			{0, 2, 0, 0},
			{0, 0, 0, 0},
		},
	},

	// skew tetro left
	{
		{
			{3, 3, 0, 0},
			{0, 3, 3, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 3, 0, 0},
			{3, 3, 0, 0},
			{3, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{3, 3, 0, 0},
			{0, 3, 3, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 3, 0, 0},
			{3, 3, 0, 0},
			{3, 0, 0, 0},
			{0, 0, 0, 0},
		},
	},

	// skew tetro right
	{
		{
			{0, 3, 3, 0},
			{3, 3, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{3, 0, 0, 0},
			{3, 3, 0, 0},
			{0, 3, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 3, 3, 0},
			{3, 3, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{3, 0, 0, 0},
			{3, 3, 0, 0},
			{0, 3, 0, 0},
			{0, 0, 0, 0},
		},
	},

	// square tetro
	{
		{
			{4, 4, 0, 0},
			{4, 4, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{4, 4, 0, 0},
			{4, 4, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{4, 4, 0, 0},
			{4, 4, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{4, 4, 0, 0},
			{4, 4, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
	},

	// L-tetro
	{
		{
			{5, 0, 0, 0},
			{5, 0, 0, 0},
			{5, 5, 0, 0},
			{0, 0, 0, 0},
		},

		{
			{0, 0, 0, 0},
			{5, 5, 5, 0},
			{5, 0, 0, 0},
			{0, 0, 0, 0},
		},

		{
			{5, 5, 0, 0},
			{0, 5, 0, 0},
			{0, 5, 0, 0},
			{0, 0, 0, 0},
		},

		{
			{0, 0, 5, 0},
			{5, 5, 5, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
	},
};

tetro_t* tetro_create(tetro_type_e tetro_type) {
	LOG("Creating tetro...");
	tetro_t* new_tetro = (tetro_t*)malloc(sizeof(tetro_t));

	ASSERT((new_tetro == NULL), "Failed to create tetro");

	new_tetro->tetro_type = tetro_type;
	new_tetro->color = TETRO_COLORS[tetro_type];
	new_tetro->is_pinned = false;
	new_tetro->grid_x = 0;
	new_tetro->grid_y = 0;
	new_tetro->curr_variation = 0;

	for (int v = 0; v < TETRO_VARIATIONS; v++) {
		for (int y = 0;y < TETRO_SQR_AREA;y++) {
			for (int x = 0;x < TETRO_SQR_AREA;x++) {
				new_tetro->data[v][y][x] = TETRO_DATA[tetro_type][v][y][x];
			}
		}
	}

	LOG("tetro created");
	return new_tetro;
}

void tetro_print(tetro_t* tetro) {
	for (int v = 0; v < TETRO_VARIATIONS; v++) {
		for (int y = 0;y < TETRO_SQR_AREA;y++) {
			for (int x = 0;x < TETRO_SQR_AREA;x++) {
				LOGF("%d\t", tetro->data[v][y][x]);
			}
			LOG("\n");
		}
		LOG("\n");
	}
}

void warn_about_tetro_state(tetro_t* tetro, int event_code) {
	LOGF("Dispatch event %d\n", event_code);
	SDL_Event event;
	SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
	event.type = event_code;
	event.user.code = event_code;
	SDL_PushEvent(&event);
}

void tetro_update_fall(tetro_t* tetro, grid_t* grid) {
	if (tetro->is_pinned) {
		for (int y = 0;y < TETRO_SQR_AREA;y++) {
			for (int x = 0;x < TETRO_SQR_AREA;x++) {
				if (tetro->data[tetro->curr_variation][y][x] != 0) {
					grid->data[tetro->grid_y + y][tetro->grid_x + x] = tetro->tetro_type * -1;
				}
			}
		}

		warn_about_tetro_state(tetro, grid->pin_event_id);
		return;
	}

	for (int y = 0;y < TETRO_SQR_AREA;y++) {
		for (int x = 0;x < TETRO_SQR_AREA;x++) {
			if (tetro->data[tetro->curr_variation][y][x] != 0) {
				if (tetro->grid_y + y + 1 >= grid->rows) {
					tetro->is_pinned = true;
					return;
				}

				if (grid->data[tetro->grid_y + y + 1][tetro->grid_x + x] != 0) {
					tetro->is_pinned = true;
					return;
				}
			}
		}
	}

	tetro->grid_y++;
}

bool can_move_right(tetro_t* tetro, grid_t* grid) {
	if (tetro->is_pinned) {
		return false;
	}

	for (int y = 0;y < TETRO_SQR_AREA;y++) {
		for (int x = 0;x < TETRO_SQR_AREA;x++) {
			if (tetro->data[tetro->curr_variation][y][x] != 0) {
				if (tetro->grid_x + x + 1 >= grid->cols) {
					return false;
				}

				if (grid->data[tetro->grid_y + y][tetro->grid_x + x + 1] != 0) {
					return false;
				}
			}
		}
	}

	return true;
}

bool can_move_left(tetro_t* tetro, grid_t* grid) {
	if (tetro->is_pinned) {
		return false;
	}

	for (int y = 0;y < TETRO_SQR_AREA;y++) {
		for (int x = 0;x < TETRO_SQR_AREA;x++) {
			if (tetro->data[tetro->curr_variation][y][x] != 0) {
				if (tetro->grid_x + x - 1 < 0) {
					return false;
				}

				if (grid->data[tetro->grid_y + y][tetro->grid_x + x - 1] != 0) {
					return false;
				}
			}
		}
	}

	return true;
}

void tetro_move_sideways(tetro_t* tetro, tetro_move_e tetro_move, grid_t* grid) {
	if (tetro_move == TETRO_MOVE_LEFT && can_move_left(tetro, grid)) {
		tetro->grid_x--;
	}

	if (tetro_move == TETRO_MOVE_RIGHT && can_move_right(tetro, grid)) {
		tetro->grid_x++;
	}
}

bool can_rotate(tetro_t* tetro, tetro_rotate_e tetro_rotate, grid_t* grid) {
	if (tetro->is_pinned) {
		return false;
	}

	int next_variation = tetro->curr_variation;

	if (tetro_rotate == TETRO_ROTATE_CCW) {
		next_variation++;
		if (next_variation >= TETRO_VARIATIONS) {
			next_variation = 0;
		}
	}

	if (tetro_rotate == TETRO_ROTATE_CW) {
		next_variation--;
		if (next_variation < 0) {
			next_variation = 3;
		}
	}

	for (int y = 0;y < TETRO_SQR_AREA;y++) {
		for (int x = 0;x < TETRO_SQR_AREA;x++) {
			if (tetro->data[next_variation][y][x] != 0) {
				if (tetro->grid_y + y >= grid->rows) {
					return false;
				}

				if (tetro->grid_x + x >= grid->cols) {
					return false;
				}

				if (tetro->grid_x + x < 0) {
					return false;
				}

				if (grid->data[tetro->grid_y + y][tetro->grid_x + x] != 0) {
					return false;
				}
			}
		}
	}

	return true;
}

void tetro_rotate(tetro_t* tetro, tetro_rotate_e tetro_rotate, grid_t* grid) {
	if (tetro_rotate == TETRO_ROTATE_CCW && can_rotate(tetro, tetro_rotate, grid)) {
		tetro->curr_variation++;
		if (tetro->curr_variation >= TETRO_VARIATIONS) {
			tetro->curr_variation = 0;
		}
	}

	if (tetro_rotate == TETRO_ROTATE_CW && can_rotate(tetro, tetro_rotate, grid)) {
		tetro->curr_variation--;
		if (tetro->curr_variation < 0) {
			tetro->curr_variation = 3;
		}
	}
}
