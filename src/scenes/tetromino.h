
#ifndef __TETROMINO_H__
#define __TETROMINO_H__

#include <SDL.h>

// straight tetromino
#define TST0 { \
	{1,0,0,0},   \
	{1,0,0,0},   \
	{1,0,0,0},   \
	{1,0,0,0},   \
}

#define TST1 {  \
	{0,0,0,0},    \
	{1,1,1,1},    \
	{0,0,0,0},    \
	{0,0,0,0},    \
}

// T-tetromino
#define TET0 {  \
	{0, 2, 0, 0}, \
	{2, 2, 2, 0}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
}

#define TET1 {  \
	{0, 2, 0, 0}, \
	{0, 2, 2, 0}, \
	{0, 2, 0, 0}, \
	{0, 0, 0, 0}, \
}

#define TET2 {  \
	{0, 0, 0, 0}, \
	{2, 2, 2, 0}, \
	{0, 2, 0, 0}, \
	{0, 0, 0, 0}, \
}

#define TET3 {  \
	{0, 2, 0, 0}, \
	{2, 2, 0, 0}, \
	{0, 2, 0, 0}, \
	{0, 0, 0, 0}, \
}

// skew tetromino
#define TSW0 {  \
	{3, 3, 0, 0}, \
	{0, 3, 3, 0}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
}

// skew tetromino
#define TSW1 {  \
	{0, 3, 0, 0}, \
	{3, 3, 0, 0}, \
	{3, 0, 0, 0}, \
	{0, 0, 0, 0}, \
}

// skew tetromino 2
#define TSWI0 { \
	{0, 3, 3, 0}, \
	{3, 3, 0, 0}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
}

// skew tetromino 2
#define TSWI1 { \
	{3, 0, 0, 0}, \
	{3, 3, 0, 0}, \
	{0, 3, 0, 0}, \
	{0, 0, 0, 0}, \
}

// square tetromino
#define TSQ0 {  \
	{4, 4, 0, 0}, \
	{4, 4, 0, 0}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
};

// L-tetromino
#define TEL0 {  \
	{5, 0, 0, 0}, \
	{5, 0, 0, 0}, \
	{5, 5, 0, 0}, \
	{0, 0, 0, 0}, \
};

#define TEL1 {  \
	{0, 0, 0, 0}, \
	{5, 5, 5, 0}, \
	{5, 0, 0, 0}, \
	{0, 0, 0, 0}, \
};

#define TEL2 {  \
	{5, 5, 0, 0}, \
	{0, 5, 0, 0}, \
	{0, 5, 0, 0}, \
	{0, 0, 0, 0}, \
};

#define TEL3 {  \
	{0, 0, 5, 0}, \
	{5, 5, 5, 0}, \
	{0, 0, 0, 0}, \
	{0, 0, 0, 0}, \
};

#define PIECE_VARIATIONS 4
#define PIECE_SQR_AREA 4

typedef struct tetromino {
	SDL_Color color;
	bool pinned;
	int type;
	int x, y;
	int size_var;
	int curr_var;
	int*** data;
} tetromino_t;

#endif // __TETROMINO_H__
