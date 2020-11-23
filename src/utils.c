#include "utils.h"

void
remove_extension(char* s)
{
	char* dot = 0;

	while (*s) {
		if (*s == '.') dot = s;  // last dot
		else if (*s == '/' || *s == '\\') dot = 0;  // ignore dots before path separators
		s++;
	}

	if (dot)
		*dot = '\0';
}
