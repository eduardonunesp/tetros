#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include "log.h"

#define RGB_WHITE 255, 255, 255
#define RGB_BLACK 0, 0, 0
#define RGB_RED 255, 0, 0
#define RGB_GREEN 0, 255, 0
#define RGB_BLUE 0, 0, 255

// M_CONC and M_CONC_ come from https://stackoverflow.com/a/14804003/7067195
#define M_CONC(A, B) M_CONC_(A, B)
#define M_CONC_(A, B) A##B

#define ENUM_COUNT_SUFFIX _count
#define ENUM_COUNT(tag) M_CONC(tag, ENUM_COUNT_SUFFIX)
#define COUNTABLE_ENUM(tag, ...) \
  typedef enum {__VA_ARGS__} tag; \
  static const int32_t ENUM_COUNT(tag) = sizeof((int32_t []) {__VA_ARGS__}) / sizeof(int32_t)

#define NEW(dtype) (dtype *)calloc(1, sizeof(dtype))
#define NEWX(dtype, length) (dtype *)calloc(length, sizeof(dtype))
#define DESTROY(var) do {free(var); var = NULL;} while(0)
#define FOR_Y(limit) for (int32_t y = 0; y < limit; y++)
#define FOR_X(limit) for (int32_t x = 0; x < limit; x++)

#define LOAD_FROM_CONST_MEM(NAME) SDL_RWFromConstMem(#NAME, sizeof(#NAME));

#define EXIT_ERR() exit(1)
#define EXIT_OK() exit(0)

#ifdef _DEBUG
#define ASSERT(result, msg) { \
	if (result) {               \
		ERR(msg);                 \
		ERRF("SDL Err %s\n", SDL_GetError()); \
	}                           \
}
#else
#define ASSERT(result, msg) { \
	if (result) {               \
		ERR(msg);                 \
		EXIT_ERR();               \
	}                           \
}
#endif

void
remove_extension(char* s);

#endif // UTILS_H
