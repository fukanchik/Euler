#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "euler/assert.h"

void FAIL(const char *fmt, ...)
{
	va_list va;

	va_start(va, fmt);

	vfprintf(stderr, fmt, va);
	fprintf(stderr, "\n");

	va_end(va);
	abort();
}
