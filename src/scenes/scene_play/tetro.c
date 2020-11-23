#include "tetro.h"
#include "log.h"
#include "utils.h"
#include "game.h"
#include "grid.h"
#include "scene_play.h"

static tetro_type_e _history = TETRO_NONE;

int32_t TETRO_DATA[TETRO_TYPES][TETRO_VARIATIONS][TETRO_SQR_AREA][TETRO_SQR_AREA] = {
	{},
	// I
	{
		{
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0},
		},
	},

	// T
	{
		{
			{0, 0, 2, 0},
			{0, 2, 2, 2},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 2, 0},
			{0, 0, 2, 2},
			{0, 0, 2, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 2, 2, 2},
			{0, 0, 2, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 2, 0},
			{0, 2, 2, 0},
			{0, 0, 2, 0},
			{0, 0, 0, 0},
		},
	},

	// Z
	{
		{
			{0, 3, 3, 0},
			{0, 0, 3, 3},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 3, 0},
			{0, 3, 3, 0},
			{0, 3, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 3, 3, 0},
			{0, 0, 3, 3},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 3, 0},
			{0, 3, 3, 0},
			{0, 3, 0, 0},
			{0, 0, 0, 0},
		},
	},

	// S
	{
		{
			{0, 0, 3, 3},
			{0, 3, 3, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 3, 0, 0},
			{0, 3, 3, 0},
			{0, 0, 3, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 3, 3},
			{0, 3, 3, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 3, 0, 0},
			{0, 3, 3, 0},
			{0, 0, 3, 0},
			{0, 0, 0, 0},
		},
	},

	// O
	{
		{
			{0, 4, 4, 0},
			{0, 4, 4, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 4, 4, 0},
			{0, 4, 4, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 4, 4, 0},
			{0, 4, 4, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 4, 4, 0},
			{0, 4, 4, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
	},

	// L
	{
		{
			{0, 5, 0, 0},
			{0, 5, 0, 0},
			{0, 5, 5, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 5, 5, 5},
			{0, 5, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 5, 5, 0},
			{0, 0, 5, 0},
			{0, 0, 5, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 0, 5},
			{0, 5, 5, 5},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
	},

	// J
	{
		{
			{0, 0, 6, 0},
			{0, 0, 6, 0},
			{0, 6, 6, 0},
			{0, 0, 0, 0},
		},
		{
			{6, 0, 0, 0},
			{6, 6, 6, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 6, 6, 0},
			{0, 6, 0, 0},
			{0, 6, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{6, 6, 6, 0},
			{0, 0, 6, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
	},
};

tetro_t*
tetro_create(tetro_type_e t_type)
{
	LOG("Creating tetro...");
	tetro_t* new_tetro = NEW(tetro_t);

	ASSERT((new_tetro == NULL), "Failed to create tetro");

	new_tetro->tetro_type = t_type;
	new_tetro->color = TETRO_COLORS[t_type];
	new_tetro->is_pinned = false;
	new_tetro->grid_x = 3;
	new_tetro->grid_y = 0;
	new_tetro->curr_rotate = 0;

	for (int32_t v = 0; v < TETRO_VARIATIONS; v++)
		for (int32_t y = 0;y < TETRO_SQR_AREA;y++)
			for (int32_t x = 0;x < TETRO_SQR_AREA;x++)
				new_tetro->data[v][y][x] = TETRO_DATA[t_type][v][y][x];

	LOG("tetro created");
	return new_tetro;
}

void
tetro_reset(tetro_t* t)
{
	t->is_pinned = false;
	t->grid_x = 3;
	t->grid_y = 0;
	t->curr_rotate = 0;
}

void
tetro_print(tetro_t* t) {
	for (int32_t v = 0; v < TETRO_VARIATIONS; v++) {
		for (int32_t y = 0;y < TETRO_SQR_AREA;y++) {
			for (int32_t x = 0;x < TETRO_SQR_AREA;x++)
				LOGF("%d\t", t->data[v][y][x]);
			LOG("\n");
		}
		LOG("\n");
	}
}

void
tetro_update_fall(tetro_t* t, grid_t* grid, scene_play_t* scn_play)
{
	if (t->is_pinned) {
		for (int32_t y = 0;y < TETRO_SQR_AREA;y++)
			for (int32_t x = 0;x < TETRO_SQR_AREA;x++)
				if (t->data[t->curr_rotate][y][x] != 0)
					grid->data[t->grid_y + y][t->grid_x + x] = t->tetro_type * -1;

		game_dispatch_event(
			scn_play->play_events.EVENT_TETRO_PINNED,
			NULL,
			NULL
		);

		return;
	}

	for (int32_t y = 0;y < TETRO_SQR_AREA;y++) {
		for (int32_t x = 0;x < TETRO_SQR_AREA;x++) {
			if (t->data[t->curr_rotate][y][x] != 0) {
				if (t->grid_y + y + 1 >= grid->rows) {
					t->is_pinned = true;
					return;
				}

				if (grid->data[t->grid_y + y + 1][t->grid_x + x] != 0) {
					t->is_pinned = true;
					return;
				}
			}
		}
	}

	if (!scn_play->game->game_params.no_fall)
		t->grid_y++;
}

bool
can_move_right(tetro_t* t, grid_t* grid)
{
	if (t->is_pinned)
		return false;

	for (int32_t y = 0;y < TETRO_SQR_AREA;y++) {
		for (int32_t x = 0;x < TETRO_SQR_AREA;x++) {
			if (t->data[t->curr_rotate][y][x] != 0) {
				if (t->grid_x + x + 1 >= grid->cols)
					return false;

				if (grid->data[t->grid_y + y][t->grid_x + x + 1] != 0)
					return false;
			}
		}
	}

	return true;
}

bool
can_move_left(tetro_t* t, grid_t* grid)
{
	if (t->is_pinned)
		return false;

	for (int32_t y = 0;y < TETRO_SQR_AREA;y++) {
		for (int32_t x = 0;x < TETRO_SQR_AREA;x++) {
			if (t->data[t->curr_rotate][y][x] != 0) {
				if (t->grid_x + x - 1 < 0)
					return false;

				if (grid->data[t->grid_y + y][t->grid_x + x - 1] != 0)
					return false;
			}
		}
	}

	return true;
}

void
tetro_move_sideways(tetro_t* t, tetro_move_e t_move, grid_t* grid)
{
	if (t_move == TETRO_MOVE_LEFT && can_move_left(t, grid))
		t->grid_x--;

	if (t_move == TETRO_MOVE_RIGHT && can_move_right(t, grid))
		t->grid_x++;
}

bool
can_rotate(tetro_t* t, tetro_rotate_e t_rotate, grid_t* grid)
{
	if (t->is_pinned)
		return false;

	int32_t next_variation = t->curr_rotate;

	if (t_rotate == TETRO_ROTATE_CCW) {
		next_variation++;
		if (next_variation >= TETRO_VARIATIONS)
			next_variation = 0;
	}

	if (t_rotate == TETRO_ROTATE_CW) {
		next_variation--;
		if (next_variation < 0)
			next_variation = 3;
	}

	for (int32_t y = 0;y < TETRO_SQR_AREA;y++) {
		for (int32_t x = 0;x < TETRO_SQR_AREA;x++) {
			if (t->data[next_variation][y][x] != 0) {
				if (t->grid_y + y >= grid->rows)
					return false;

				if (t->grid_x + x >= grid->cols)
					return false;

				if (t->grid_x + x < 0)
					return false;

				if (grid->data[t->grid_y + y][t->grid_x + x] != 0)
					return false;
			}
		}
	}

	return true;
}

void
tetro_rotate(tetro_t* t, tetro_rotate_e t_rotate, grid_t* grid)
{
	if (t_rotate == TETRO_ROTATE_CCW && can_rotate(t, t_rotate, grid)) {
		t->curr_rotate++;
		if (t->curr_rotate >= TETRO_VARIATIONS)
			t->curr_rotate = 0;
	}

	if (t_rotate == TETRO_ROTATE_CW && can_rotate(t, t_rotate, grid)) {
		t->curr_rotate--;
		if (t->curr_rotate < 0)
			t->curr_rotate = 3;
	}
}

// TODO: This can be improved to do a better distribution
tetro_type_e
tetro_take_piece()
{
	int32_t piece = rand() % (TETRO_TYPES - 1) + 1;

	if (piece == _history)
		piece = rand() % (TETRO_TYPES - 1) + 1;

	_history = piece;
	LOGF("Next piece %d\n", piece);
	return piece;
}
