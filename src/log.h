
#ifndef __LOG_H__
#define __LOG_H__

#include <stdlib.h>
#include <stdio.h>

#ifdef _DEBUG
#define LOG(msg) fprintf(stdout, "%s\n", msg)
#define LOGF(fmt, ...) fprintf(stdout, fmt, __VA_ARGS__)
#define ERR(msg) fprintf(stderr, "%s\n", msg)
#define ERRF(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define LOG(fmt)
#define LOGF(fmt, ...)
#define ERR(msg)
#define ERRF(fmt, ...)
#endif

#endif // __LOG_H__
