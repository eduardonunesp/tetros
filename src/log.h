
#ifndef __LOG_H__
#define __LOG_H__

#include <stdlib.h>
#include <stdio.h>

#ifdef _DEBUG
#define LOG(msg) printf(msg);
#define LOGF(fmt, ...) fprintf(stdout, fmt, __VA_ARGS__)
#else
#define LOG(fmt)
#define LOGF(fmt, ...)
#endif

#endif // __LOG_H__
