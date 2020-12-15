#ifndef __UTILS_H__
#define __UTILS_H__

#include <assert.h>
#include <stdlib.h>
#include "log.h"

#define TIME_SECOND 100
#define FOR_Y(limit) for (int y = 0; y < limit; y++)
#define FOR_X(limit) for (int x = 0; x < limit; x++)

#define EXIT_ERR() exit(1)
#define EXIT_OK() exit(0)

#ifdef _DEBUG
#define ASSERT(result, msg) { \
	if (result) {               \
		ERR(msg);                 \
		assert(result);           \
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

#endif // __UTILS_H__
