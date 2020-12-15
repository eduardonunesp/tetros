#include "tetro.h"
#include "../log.h"
#include "../utils.h"


SDL_Color TETRO_COLORS[TETRO_TYPES] = {
	{0,   255, 255, 255},
	{255, 0,   255, 255},
	{255, 0,   0,   255},
	{255, 0,   0,   255},
	{255, 255, 0,   255},
	{0,   0,   255, 255},
};

int TETRO_DATA[TETRO_TYPES][TETRO_VARIATIONS][TETRO_SQR_AREA][TETRO_SQR_AREA] = {
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
